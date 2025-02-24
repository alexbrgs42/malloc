# include "../include/malloc.h"

void    *ft_realloc(void *ptr, size_t size) {
    size_t      allocated_size;
    size_t      available_size;
    t_metadata  *meta;


    pthread_mutex_lock(&memory);
    if (ptr == NULL) {
        pthread_mutex_unlock(&memory);
        return ft_malloc(size);
    }
    if (size == 0) {
        pthread_mutex_unlock(&memory);
        ft_free(ptr);
        return NULL;
    }
    meta = (t_metadata *)(ptr - sizeof(t_metadata));
    if (meta->size - sizeof(t_metadata) == size) {
        pthread_mutex_unlock(&memory);
        return ptr;
    }
    available_size = available_size_for_realloc(meta);
    if (available_size < size) {
        return increase_realloc_at_different_address(ptr, size);
    }
    allocated_size = size + sizeof(t_metadata);
    if (meta->size < allocated_size)
        increase_realloc_at_same_address(meta, allocated_size);
    else
        decrease_realloc(meta, allocated_size);
    pthread_mutex_unlock(&memory);
    return ptr;
}

void    *increase_realloc_at_different_address(void *ptr, size_t size) {
    void    *new_ptr;

    pthread_mutex_unlock(&memory);
    new_ptr = ft_malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }
    pthread_mutex_lock(&memory);
    fill_reallocated_block(new_ptr, ptr);
    pthread_mutex_unlock(&memory);
    ft_free(ptr);
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

void    increase_realloc_at_same_address(t_metadata *meta, size_t size) {
    if (((t_metadata *)meta->next)->next == NULL && meta->next + ((t_metadata *)meta->next)->size < (void *)meta + size + sizeof(t_metadata)) {
        set_metadata(meta, size, meta->prev, NULL, true);
    }
    else {
        set_metadata((void *)meta + size, ((t_metadata *)meta->next)->size - (size - meta->size),meta, ((t_metadata *)meta->next)->next, false);
        set_metadata(meta, size, meta->prev, (void *)meta + size, true);
        if (((t_metadata *)meta->next)->next != NULL)
            set_metadata(((t_metadata *)meta->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->size, meta->next, ((t_metadata *)((t_metadata *)meta->next)->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->is_malloc);
    }
}

void    decrease_realloc(t_metadata *meta, size_t size) {
    if (meta->next != NULL) {
        set_metadata((void *)meta + size, ((t_metadata *)meta->next)->size - (size - meta->size), meta, ((t_metadata *)meta->next)->next, true);
        set_metadata(meta, size, meta->prev, (void *)meta + size, true);
        if (((t_metadata *)meta->next)->next != NULL)
            set_metadata(((t_metadata *)meta->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->size, meta->next, ((t_metadata *)((t_metadata *)meta->next)->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->is_malloc);
    }
    else {
        set_metadata((void *)meta + size, meta->size - size, meta, NULL, false);
        set_metadata(meta, size, meta->prev, (void *)meta + size, true);
    }
    pthread_mutex_unlock(&memory);
    ft_free(meta->next + sizeof(t_metadata));
    pthread_mutex_lock(&memory);
}
