#include "../include/malloc.h"

void    *ft_malloc(size_t size) {
    size_t  allocated_size = size + sizeof(t_metadata);
    void    *ptr = NULL;

    if (size <= 0)
        return NULL;

    pthread_mutex_lock(&memory);
    // TINY
    if (allocated_size <= (size_t)(N / 100))
        ptr = tiny_small_allocation(allocated_size, TINY);
    // SMALL
    else if (allocated_size <= (size_t)(M / 100))
        ptr = tiny_small_allocation(allocated_size, SMALL);
    // LARGE
    else if (allocated_size > (size_t)(M / 100))
        ptr = large_allocation(allocated_size);

    // TOO BIG
    // TODO

    pthread_mutex_unlock(&memory);
    return ptr;
}

// check mutex
void    *ft_realloc(void *ptr, size_t size) {
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
    t_metadata  *meta = (t_metadata *)(ptr - sizeof(t_metadata));
    if (meta->size - sizeof(t_metadata) == size) {
        pthread_mutex_unlock(&memory);
        return ptr;
    }
    size_t available_size = realloc_available_size(meta);
    if (available_size < size) {
        pthread_mutex_unlock(&memory);
        void *new_ptr = ft_malloc(size);
        if (new_ptr == NULL) {
            return NULL;
        }
        pthread_mutex_lock(&memory);
        fill_reallocated_block(new_ptr, ptr);
        pthread_mutex_unlock(&memory);
        ft_free(ptr);
        return new_ptr;
    }
    if (meta->size - sizeof(t_metadata) < size) {
        // increase size
    }
    else {
        // mark_block((void *)meta, size); // should adapt is_malloc
        pthread_mutex_unlock(&memory);
        ft_free(meta->next);
        return ptr;
    }
    pthread_mutex_unlock(&memory);
}

size_t  realloc_available_size(t_metadata *meta) {
    size_t  size = meta->size - sizeof(t_metadata);

    if (meta->next == NULL || ((t_metadata *)meta->next)->is_malloc == true)
        return size;
    return size + ((t_metadata *)meta->next)->size;
}

void    *ft_calloc(size_t nmemb, size_t size); // mutex

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

void    *tiny_small_allocation(size_t size, t_type type) {
    void *ptr = get_block(size, type);
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
