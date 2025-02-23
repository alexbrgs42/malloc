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
    size_t  allocated_size = size + sizeof(t_metadata);
    if (meta->size < allocated_size) {
        // INCREASE
        if (((t_metadata *)meta->next)->next == NULL && meta->next + ((t_metadata *)meta->next)->size < (void *)meta + allocated_size + sizeof(t_metadata)) {
            set_metadata((void *)meta, allocated_size, meta->prev, NULL, true);
        }
        else {
            set_metadata((void *)meta + allocated_size, ((t_metadata *)meta->next)->size - (allocated_size - meta->size), (void *)meta, ((t_metadata *)meta->next)->next, false);
            set_metadata((void *)meta, allocated_size, meta->prev, (void *)meta + allocated_size, true);
            if (((t_metadata *)meta->next)->next != NULL)
                set_metadata(((t_metadata *)meta->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->size, meta->next, ((t_metadata *)((t_metadata *)meta->next)->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->is_malloc);
        }
    }
    else {
        // DECREASE
        if (meta->next != NULL) {
            set_metadata((void *)meta + allocated_size, ((t_metadata *)meta->next)->size - (allocated_size - meta->size), (void *)meta, ((t_metadata *)meta->next)->next, true);
            set_metadata((void *)meta, allocated_size, meta->prev, (void *)meta + allocated_size, true);
            if (((t_metadata *)meta->next)->next != NULL)
                set_metadata(((t_metadata *)meta->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->size, meta->next, ((t_metadata *)((t_metadata *)meta->next)->next)->next, ((t_metadata *)((t_metadata *)meta->next)->next)->is_malloc);
        }
        else {
            set_metadata((void *)meta + allocated_size, meta->size - allocated_size, (void *)meta, NULL, false);
            set_metadata((void *)meta, allocated_size, meta->prev, (void *)meta + allocated_size, true);
        }
        pthread_mutex_unlock(&memory);
        ft_free(meta->next + sizeof(t_metadata));
        return ptr;
    }
    pthread_mutex_unlock(&memory);
    return ptr;
}

void    fill_reallocated_block(void *new_ptr, void *ptr) {
    t_metadata  *meta = (t_metadata *)(ptr - sizeof(t_metadata));
    t_metadata  *new_meta = (t_metadata *)(new_ptr - sizeof(t_metadata));
    size_t      size = meta->size - sizeof(t_metadata);
    size_t      new_size = new_meta->size - sizeof(t_metadata);

    for (size_t i = 0; i < size && i < new_size; i++)
        ((char *)new_ptr)[i] = ((char *)ptr)[i];
}

size_t  realloc_available_size(t_metadata *meta) {
    size_t  size = meta->size - sizeof(t_metadata);

    if (meta->next == NULL || ((t_metadata *)meta->next)->is_malloc == true)
        return size;
    return size + ((t_metadata *)meta->next)->size;
}

void    *ft_calloc(size_t nmemb, size_t size) {
    void    *ptr;
    pthread_mutex_lock(&memory);
    if (nmemb * size == 0) {
        pthread_mutex_unlock(&memory);
        return NULL;
    }
    if (nmemb * size < 0 || nmemb * size < nmemb || nmemb * size < size) {
        pthread_mutex_unlock(&memory);
        return NULL;
    }
    pthread_mutex_unlock(&memory);
    ptr = ft_malloc(nmemb * size);
    if (ptr == NULL)
        return NULL;
    pthread_mutex_lock(&memory);
    for (size_t i = 0; i < nmemb * size; i++)
        ((char *)ptr)[i] = 0;
    pthread_mutex_unlock(&memory);
    return ptr;
}

bool    is_block_allocated(void *meta_addr) {
    t_arena    *curr_arena;
    t_metadata  *curr_meta;

    if (arenas == NULL || arenas->arenas == NULL)
        return false;
    curr_arena = arenas->arenas;
    while (curr_arena != NULL && (curr_arena->addr > meta_addr || curr_arena->addr + curr_arena->size <= meta_addr))
        curr_arena = curr_arena->next;
    if (curr_arena == NULL)
        return false;
    curr_meta = (t_metadata *)curr_arena;
    while (curr_meta != NULL) {
        if ((void *)curr_meta == meta_addr)
            return (curr_meta->is_malloc);
        curr_meta = (t_metadata *)(curr_meta->next);
    }
    return false;
}

void    ft_free(void *ptr) {
    if (ptr == NULL)
        return ;

    pthread_mutex_lock(&memory);
    t_metadata  *free_meta = (t_metadata *)(ptr - sizeof(t_metadata));
    // CHANGE ALLOCATED STATUS
    if (is_block_allocated((void *)free_meta) == false) {
        printf("Error: Block cannot be freed.\n");
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
