#include "../include/malloc.h"

// 1 global for allocation management and 1 for thread safety

void    *ft_realloc(void *ptr, size_t size); // mutex

void    ft_free(void *ptr) {

    if (ptr == NULL)
        return ;

    pthread_mutex_lock(&memory);
    // CHANGE BIT

    // DOESN'T FREE ARENA IF ALLOC REMAINING IN TINY OR SMALL

    // KEEP IN MEMORY FREE ZONE

    // COALESCING (DEFRAGMENTATION)
    pthread_mutex_unlock(&memory);
}

// enum for exit status ?
void    *ft_malloc(size_t size) {

    size_t  allocated_size = ALIGN(size + sizeof(t_metadata));
    void    *result = NULL;

    if (size <= 0)
        return NULL;

    pthread_mutex_lock(&memory);
    // TINY
    if (allocated_size <= (size_t)(N / 100))
        result = tiny_allocation(allocated_size);
    // SMALL
    else if (allocated_size <= (size_t)(M / 100))
        result = small_allocation(allocated_size);
    // LARGE
    else if (allocated_size > (size_t)(M / 100))
        result = large_allocation(allocated_size);

    // TOO BIG

    // HANDLE STATUS

    pthread_mutex_unlock(&memory);
    return result;
}

void set_metadata(size_t *ptr, size_t size, size_t *prev, size_t *next) {
    t_metadata  header = { size, prev, next };
    *(t_metadata *)ptr = header;
}

void    *tiny_allocation(size_t size) {

    size_t *ptr = best_fit(size, TINY);
    if (ptr == NULL)
        return NULL;

    mark_chunk((t_metadata *)ptr, size);

    return (void *)(ptr + sizeof(t_metadata));
}

void    *small_allocation(size_t size) {

    size_t *ptr = best_fit(size, SMALL);
    if (ptr == NULL)
        return NULL;

    mark_chunk((t_metadata *)ptr, size);

    return (void *)(ptr + sizeof(t_metadata));
}

void    *large_allocation(size_t size) {

    (void)size;

    // MAX SIZE ?

    // MMAP

    // MARK FIRST BIT
    return NULL; // change
}

void    mark_chunk(t_metadata *ptr, size_t size) {

    if (ptr->size != size)
        set_metadata((size_t *)(ptr + size), ptr->size - size, (size_t *)ptr, ptr->next);
    if (ptr->next != NULL)
        set_metadata(ptr->next, ((t_metadata *)(ptr->next))->size, (size_t *)(ptr + size), ((t_metadata *)(ptr->next))->next);
    set_metadata((size_t *)ptr, size, ptr->prev, (ptr->size != size ? (size_t *)(ptr + size) : ptr->next));
    ptr->size = USED_BLOCK(ptr->size);
}

// REMOVE ft_