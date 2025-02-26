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
    if (get_block_size(meta) - sizeof(t_metadata) == size) {
        pthread_mutex_unlock(&memory);
        return ptr;
    }
    available_size = available_size_for_realloc(meta);
    allocated_size = ALIGN(size + sizeof(t_metadata));
    if (available_size < size)
        return increase_realloc_at_different_address(ptr, size);
    if (get_block_size(meta) < allocated_size)
        increase_realloc_at_same_address(meta, allocated_size, size);
    else
        decrease_realloc(meta, allocated_size, size);
    pthread_mutex_unlock(&memory);
    return ptr;
}

void    *increase_realloc_at_different_address(void *ptr, size_t size) {
    void    *new_ptr;

    pthread_mutex_unlock(&memory);
    new_ptr = malloc(size);
    if (new_ptr == NULL)
        return NULL;
    pthread_mutex_lock(&memory);
    fill_reallocated_block(new_ptr, ptr);
    pthread_mutex_unlock(&memory);
    free(ptr);
    return new_ptr;
}

size_t  available_size_for_realloc(t_metadata *meta) {
    size_t  size;
    
    size = get_block_size(meta) - sizeof(t_metadata);
    if (meta->next == NULL || ((t_metadata *)meta->next)->is_malloc == true)
        return size;
    return size + get_block_size(((t_metadata *)meta->next));
}

void    fill_reallocated_block(void *new_ptr, void *ptr) {
    size_t      size;
    size_t      new_size;
    t_metadata  *meta;
    t_metadata  *new_meta;

    meta = (t_metadata *)(ptr - sizeof(t_metadata));
    new_meta = (t_metadata *)(new_ptr - sizeof(t_metadata));
    size = get_block_size(meta) - sizeof(t_metadata);
    new_size = get_block_size(new_meta) - sizeof(t_metadata);
    for (size_t i = 0; i < size && i < new_size; i++)
        ((char *)new_ptr)[i] = ((char *)ptr)[i];
}

void    increase_realloc_at_same_address(void *ptr, size_t block_size, size_t size) {
    t_metadata  *meta;
    t_metadata  *next_meta;
    t_metadata  *next_next_meta;

    meta = (t_metadata *)ptr;
    next_meta = ((t_metadata *)meta->next);
    next_next_meta = ((t_metadata *)next_meta->next);
    if ((void *)next_meta + get_block_size(next_meta) < ptr + block_size + sizeof(t_metadata)) {
        block_size = get_block_size(meta) + get_block_size(next_meta);
    }
    if (block_size == get_block_size(meta) + get_block_size(next_meta)) {
        set_metadata(ptr, size, meta->prev, next_next_meta, true);
        if (next_next_meta != NULL)
            set_metadata(next_next_meta, get_block_size(next_meta), ptr, next_next_meta->next, next_next_meta->is_malloc);
        return ;
    }
    set_metadata(ptr + block_size, get_block_size(next_meta) - (block_size - get_block_size(meta)), ptr, next_next_meta, false);
    if (next_next_meta != NULL)
        set_metadata(next_next_meta, get_block_size(next_meta), ptr + block_size, next_next_meta->next, next_next_meta->is_malloc);
    set_metadata(ptr, size, meta->prev, ptr + block_size, true);
}

void    decrease_realloc(void *ptr, size_t block_size, size_t size) {
    t_metadata  *meta;
    t_metadata  *next_meta;
    t_metadata  *next_next_meta;

    meta = (t_metadata *)ptr;
    next_meta = ((t_metadata *)meta->next);
    if (get_block_size(meta) - block_size < sizeof(t_metadata) && (next_meta == NULL || next_meta->is_malloc == true))
        return ;
    if (next_meta == NULL) {
        set_metadata(ptr + block_size, get_block_size(meta) - block_size, ptr, NULL, false);
        set_metadata(ptr, size, meta->prev, ptr + block_size, true);
        return ;
    }
    if (next_meta->is_malloc == true) {
        set_metadata(ptr + block_size, get_block_size(meta) - block_size, ptr, next_meta, false);
        set_metadata(next_meta, get_block_size(next_meta), ptr + block_size, next_meta->next, next_meta->is_malloc);
        set_metadata(ptr, size, meta->prev, ptr + block_size, true);
        return ;
    }
    next_next_meta = ((t_metadata *)next_meta->next);
    set_metadata(ptr + block_size, get_block_size(next_meta) + (get_block_size(meta) - block_size), ptr, next_next_meta, false);
    if (next_next_meta != NULL)
        set_metadata(next_next_meta, get_block_size(next_meta), ptr + block_size, next_next_meta->next, next_next_meta->is_malloc);
    set_metadata(ptr, size, meta->prev, ptr + block_size, true);
    pthread_mutex_unlock(&memory);
    free(meta->next + sizeof(t_metadata));
    pthread_mutex_lock(&memory);
}
