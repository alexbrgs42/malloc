# include "../include/malloc.h"

t_allocs        *allocated_pages = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;

void    *malloc(size_t size) {
    size_t  allocated_size;
    void    *ptr;

    if (size <= 0)
        return NULL;
    pthread_mutex_lock(&memory);
    if (size > SIZE_MAX - sizeof(t_metadata)) {
        ft_printf("Error: Overflow.\n");
        pthread_mutex_unlock(&memory);
        return NULL;
    }
    allocated_size = ALIGN(size + sizeof(t_metadata));
    if (allocated_size <= (size_t)(N / 100))
        ptr = tiny_small_allocation(allocated_size, size, TINY);
    else if (allocated_size <= (size_t)(M / 100))
        ptr = tiny_small_allocation(allocated_size, size, SMALL);
    else if (allocated_size > (size_t)(M / 100))
        ptr = large_allocation(allocated_size, size);
    pthread_mutex_unlock(&memory);
    return ptr;
}

void    *tiny_small_allocation(size_t block_size, size_t size, t_type type) {
    void    *ptr;
    
    ptr = get_block(block_size, type);
    if (ptr == NULL)
        return NULL;
    mark_block(ptr, block_size, size);
    return (ptr + sizeof(t_metadata));
}

void    *large_allocation(size_t block_size, size_t size) {
    int     ret;
    void    *ptr;
    
    ptr = mmap(NULL, block_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (ptr == MAP_FAILED) {
        ft_printf("Error: mmap syscall failed.\n");
        return NULL;
    }
    if (allocated_pages == NULL) {
        create_allocated_pages(sizeof(t_allocs *) + 300 * sizeof(t_arena));
        if (allocated_pages == NULL)
            return NULL;
    }
    ret = add_arena_to_allocated_pages(ptr, LARGE, block_size);
    if (ret == EXIT_FAILURE)
        return NULL;
    set_metadata(ptr, size, NULL, NULL, true);
    return (ptr + sizeof(t_metadata));
}
