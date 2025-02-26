# include "../include/malloc.h"

void    *realloc(void *ptr, size_t size) {
    size_t      allocated_size;
    size_t      available_size;
    t_metadata  *meta;

    pthread_mutex_lock(&memory);
    if (ptr == NULL) {
        pthread_mutex_unlock(&memory);
        return malloc(size);
    }
    if (size == 0) {
        pthread_mutex_unlock(&memory);
        free(ptr);
        return NULL;
    }
    meta = (t_metadata *)(ptr - sizeof(t_metadata));
    if (meta->size - sizeof(t_metadata) == size) {
        pthread_mutex_unlock(&memory);
        return ptr;
    }
    available_size = available_size_for_realloc(meta);
    allocated_size = ALIGN(size + sizeof(t_metadata));
    if (available_size < size)
        return increase_realloc_at_different_address(ptr, allocated_size);
    if (meta->size < allocated_size) {
        increase_realloc_at_same_address((void *)meta, allocated_size);
    }
    else {
        decrease_realloc((void *)meta, allocated_size);
    }
    pthread_mutex_unlock(&memory);
    return ptr;
}

void    *increase_realloc_at_different_address(void *ptr, size_t size) {
    void    *new_ptr;

    pthread_mutex_unlock(&memory);
    new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }
    pthread_mutex_lock(&memory);
    fill_reallocated_block(new_ptr, ptr);
    pthread_mutex_unlock(&memory);
    free(ptr);
    return new_ptr;
}

size_t  available_size_for_realloc(t_metadata *meta) {
    size_t  size;
    
    size = meta->size - sizeof(t_metadata);
    if (meta->next == NULL || ((t_metadata *)meta->next)->is_malloc == true)
        return size;
    return size + ((t_metadata *)meta->next)->size;
}

void    fill_reallocated_block(void *new_ptr, void *ptr) {
    size_t      size;
    size_t      new_size;
    t_metadata  *meta;
    t_metadata  *new_meta;

    meta = (t_metadata *)(ptr - sizeof(t_metadata));
    new_meta = (t_metadata *)(new_ptr - sizeof(t_metadata));
    size = meta->size - sizeof(t_metadata);
    new_size = new_meta->size - sizeof(t_metadata);
    for (size_t i = 0; i < size && i < new_size; i++)
        ((char *)new_ptr)[i] = ((char *)ptr)[i];
}

void    increase_realloc_at_same_address(void *ptr, size_t size) {
    t_metadata  *meta;
    t_metadata  *next_meta;
    t_metadata  *next_next_meta;

    meta = (t_metadata *)ptr;
    next_meta = ((t_metadata *)meta->next);
    next_next_meta = ((t_metadata *)next_meta->next);
    if ((void *)next_meta + next_meta->size < ptr + size + sizeof(t_metadata)) {
        size = meta->size + next_meta->size;
    }
    if (size == meta->size + next_meta->size) {
        set_metadata(ptr, size, meta->prev, next_next_meta, true);
        if (next_next_meta != NULL) {
            set_metadata(next_next_meta, next_next_meta->size, ptr, next_next_meta->next, next_next_meta->is_malloc);
        }
        return ;
    }
    set_metadata(ptr + size, next_meta->size - (size - meta->size), ptr, next_next_meta, false);
    if (next_next_meta != NULL)
        set_metadata(next_next_meta, next_next_meta->size, ptr + size, next_next_meta->next, next_next_meta->is_malloc);
    set_metadata(ptr, size, meta->prev, ptr + size, true);
}

void    decrease_realloc(void *ptr, size_t size) {
    t_metadata  *meta;
    t_metadata  *next_meta;
    t_metadata  *next_next_meta;

    meta = (t_metadata *)ptr;
    next_meta = ((t_metadata *)meta->next);
    
    if (meta->size - size < sizeof(t_metadata) && (next_meta == NULL || next_meta->is_malloc == true))
        return ;
    if (next_meta == NULL) {
        set_metadata(ptr + size, meta->size - size, ptr, NULL, false);
        set_metadata(ptr, size, meta->prev, ptr + size, true);
        return ;
    }
    if (next_meta->is_malloc == true) {
        set_metadata(ptr + size, meta->size - size, ptr, next_meta, false);
        set_metadata(next_meta, next_meta->size, ptr + size, next_meta->next, next_meta->is_malloc);
        set_metadata(ptr, size, meta->prev, ptr + size, true);
        return ;
    }
    next_next_meta = ((t_metadata *)next_meta->next);
    set_metadata(ptr + size, next_meta->size + (meta->size - size), ptr, next_next_meta, false);
    if (next_next_meta != NULL)
        set_metadata(next_next_meta, next_next_meta->size, ptr + size, next_next_meta->next, next_next_meta->is_malloc);
    set_metadata(ptr, size, meta->prev, ptr + size, true);

    pthread_mutex_unlock(&memory);
    free(meta->next + sizeof(t_metadata));
    pthread_mutex_lock(&memory);
}
