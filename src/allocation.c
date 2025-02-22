#include "../include/malloc.h"

void    *ft_realloc(void *ptr, size_t size); // mutex

void    ft_free(void *ptr) {
    if (ptr == NULL)
        return ;

    pthread_mutex_lock(&memory);
    t_metadata  *free_meta = (t_metadata *)(ptr - sizeof(t_metadata));
    // CHANGE ALLOCATED STATUS
    if (free_meta->is_malloc == false) {
        printf("Error: Block already freed.\n");
        pthread_mutex_unlock(&memory);
        return ;
    }
    free_meta->is_malloc = false;

    // COALESCING (DEFRAGMENTATION)
    if (is_block_free(free_meta->next) == true)
        defragment((void *)free_meta, free_meta->next);
    if (is_block_free(free_meta->prev) == true) {
        free_meta = (t_metadata *)free_meta->prev;
        defragment(free_meta, free_meta->next);
    }

    // MUNMAP ARENA IF NO ALLOCATED BLOCK REMAINING
    if (free_meta->prev == NULL && free_meta->next == NULL) {
        t_arena *curr_arena = arenas->arenas;
        if (curr_arena->addr == free_meta) {
            arenas->arenas = arenas->arenas->next;
        }
        else {
            while (curr_arena->next->addr != free_meta)
                curr_arena = curr_arena->next;
            curr_arena->next = curr_arena->next->next;
        }
        munmap(free_meta, free_meta->size); // check status ?
        if (arenas->arenas == NULL) {
            munmap(arenas, arenas->mmap_size);
            arenas = NULL;
        }
    }
    pthread_mutex_unlock(&memory);
}

void    defragment(void *first_block, void *second_block) {
    t_metadata  *first_meta = (t_metadata *)first_block;
    t_metadata  *second_meta = (t_metadata *)second_block;

    set_metadata(first_block, first_meta->size + second_meta->size, first_meta->prev, second_meta->next, false);
    if (second_meta->next != NULL)
        set_metadata(second_meta->next, ((t_metadata *)second_meta->next)->size, first_block, ((t_metadata *)second_meta->next)->next, true);
    ft_bzero(second_block, sizeof(t_metadata));
}

bool    is_block_free(void *block) {
    return (block != NULL && ((t_metadata *)block)->is_malloc == false);
}

void    *ft_malloc(size_t size) {
    size_t  allocated_size = size + sizeof(t_metadata);
    void    *ptr = NULL;

    if (size <= 0)
        return NULL;

    pthread_mutex_lock(&memory);
    // TINY
    if (allocated_size <= (size_t)(N / 100))
        ptr = tiny_allocation(allocated_size);
    // SMALL
    else if (allocated_size <= (size_t)(M / 100))
        ptr = small_allocation(allocated_size);
    // LARGE
    else if (allocated_size > (size_t)(M / 100))
        ptr = large_allocation(allocated_size);

    // TOO BIG
    // TODO

    pthread_mutex_unlock(&memory);
    return ptr;
}

void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc) {
    ptr->size = size;
    ptr->prev = prev;
    ptr->next = next;
    ptr->is_malloc = is_malloc;
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
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;
    ft_bzero(ptr, size);
    add_arena(ptr, LARGE, size);
    set_metadata(ptr, size, NULL, NULL, true);
    return (void *)(ptr + sizeof(t_metadata));
}

void    mark_block(void *ptr, size_t size) {
    if (((t_metadata *)ptr)->size != size) {
        set_metadata(ptr + size, ((t_metadata *)ptr)->size - size, ptr, ((t_metadata *)ptr)->next, false);
    }
    if (((t_metadata *)ptr)->next != NULL)
        set_metadata(((t_metadata *)ptr)->next, ((t_metadata *)(((t_metadata *)ptr)->next))->size, ptr + size, ((t_metadata *)(((t_metadata *)ptr)->next))->next, ((t_metadata *)(((t_metadata *)ptr)->next))->is_malloc);
    set_metadata(ptr, size, ((t_metadata *)ptr)->prev, (((t_metadata *)ptr)->size != size ? ptr + size : ((t_metadata *)ptr)->next), true);
    ((t_metadata *)ptr)->size = ((t_metadata *)ptr)->size;
}
