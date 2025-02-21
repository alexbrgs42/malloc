#include "../include/malloc.h"

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

void    *ft_malloc(size_t size) {

    size_t  aligned_size = ALIGN(size + sizeof(t_metadata));
    void    *ptr = NULL;

    if (size <= 0)
        return NULL;

    pthread_mutex_lock(&memory);
    // TINY
    if (aligned_size <= (size_t)(N / 100))
        ptr = tiny_allocation(aligned_size);
    // SMALL
    else if (aligned_size <= (size_t)(M / 100))
        ptr = small_allocation(aligned_size);
    // LARGE
    else if (aligned_size > (size_t)(M / 100))
        ptr = large_allocation(aligned_size);

    // TOO BIG

    pthread_mutex_unlock(&memory);
    return ptr;
}

void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next) {
    ptr->size = size;
    ptr->prev = prev;
    ptr->next = next;
}

void    *tiny_allocation(size_t size) {

    void *ptr = get_block(size, TINY);
    if (ptr == NULL)
        return NULL;
    mark_block(ptr, size);
    return (void *)(ptr + sizeof(t_metadata));
}

void    *small_allocation(size_t size) {

    void *ptr = get_block(size, SMALL);
    if (ptr == NULL)
        return NULL;
    mark_block(ptr, size);
    return (void *)(ptr + sizeof(t_metadata));
}

void    *large_allocation(size_t size) {

    size_t  aligned_size = ALIGN(size + sizeof(t_metadata));

    void *ptr = mmap(NULL, aligned_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;
    ft_bzero(ptr, aligned_size);
    add_arena(ptr, LARGE, aligned_size);
    set_metadata(ptr, USED_BLOCK(aligned_size), NULL, NULL);
    return (void *)(ptr + sizeof(t_metadata));
}

// verify that used or unused block is maintained with size calculation

void    mark_block(void *ptr, size_t size) {

    if (ABSOLUT_SIZE(((t_metadata *)ptr)->size) != size) {
        set_metadata(ptr + size, ABSOLUT_SIZE(((t_metadata *)ptr)->size) - size, ptr, ((t_metadata *)ptr)->next);
    }
    if (((t_metadata *)ptr)->next != NULL)
        set_metadata(((t_metadata *)ptr)->next, ((t_metadata *)(((t_metadata *)ptr)->next))->size, ptr + size, ((t_metadata *)(((t_metadata *)ptr)->next))->next);
    set_metadata(ptr, size, ((t_metadata *)ptr)->prev, (ABSOLUT_SIZE(((t_metadata *)ptr)->size) != size ? ptr + size : ((t_metadata *)ptr)->next));
    ((t_metadata *)ptr)->size = USED_BLOCK(((t_metadata *)ptr)->size);
}
