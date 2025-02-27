# include "../include/malloc.h"

void    free(void *ptr) {
    t_metadata  *free_meta;

    if (ptr == NULL)
        return ;
    pthread_mutex_lock(&memory);
    free_meta = (t_metadata *)(ptr - sizeof(t_metadata));
    if (is_block_freeable(free_meta) == false) {
        ft_printf("Error: block cannot be freed.\n");
        pthread_mutex_unlock(&memory);
        return ;
    }
    set_metadata(free_meta, get_block_size(free_meta), free_meta->prev, free_meta->next, false);
    if (is_block_free(free_meta->next) == true) {
        defragment(free_meta, free_meta->next);
    }
    if (is_block_free(free_meta->prev) == true) {
        free_meta = (t_metadata *)free_meta->prev;
        defragment(free_meta, free_meta->next);
    }
    free_arena_if_empty(free_meta);
    pthread_mutex_unlock(&memory);
}

/// @brief Defragment two adjacent free blocks.
/// @param first_block 
/// @param second_block 
void    defragment(void *first_block, void *second_block) {
    t_metadata  *first_meta;
    t_metadata  *second_meta;
    t_metadata  *next_meta;

    first_meta = (t_metadata *)first_block;
    second_meta = (t_metadata *)second_block;
    set_metadata(first_block, get_block_size(first_meta) + get_block_size(second_meta), first_meta->prev, second_meta->next, false);
    if (second_meta->next != NULL) {
        next_meta = (t_metadata *)second_meta->next;
        set_metadata(next_meta, next_meta->size, first_block, next_meta->next, next_meta->is_malloc);
    }
}

bool    is_block_free(void *block) {
    return (block != NULL && ((t_metadata *)block)->is_malloc == false);
}

/// @brief Frees the corresponding arena if it is empty (except if it is the last arena mmaped).
/// @param free_meta the metadata freedcontained in arena
void    free_arena_if_empty(t_metadata *free_meta) {
    t_arena *arena;

    arena = allocated_pages->arenas;
    if (free_meta->prev != NULL || free_meta->next != NULL)
        return ;
    if (arena->next == NULL)
        return ;
    if (arena->addr == free_meta)
        allocated_pages->arenas = allocated_pages->arenas->next;
    else {
        while (arena->next->addr != free_meta)
            arena = arena->next;
        arena->next = arena->next->next;
    }
    munmap(free_meta, get_block_size(free_meta));
    if (allocated_pages->arenas == NULL) {
        munmap(allocated_pages, allocated_pages->mmap_size);
        allocated_pages = NULL;
    }
}

/// @brief Checks if the given pointer is inside an existing arena and if it has been malloc'd.
/// @param meta_addr The address of the metadata of the given pointer.
/// @return 
bool    is_block_freeable(void *meta_addr) {
    t_arena     *arena;
    t_metadata  *curr_meta;

    if (allocated_pages == NULL || allocated_pages->arenas == NULL)
        return false;
    arena = get_arena_of_block(meta_addr);
    if (arena == NULL)
        return false;
    curr_meta = (t_metadata *)arena;
    while (curr_meta != NULL) {
        if ((void *)curr_meta == meta_addr)
            return curr_meta->is_malloc;
        curr_meta = (t_metadata *)curr_meta->next;
    }
    return false;
}
