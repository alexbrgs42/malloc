# include "../include/malloc.h"

void    free(void *ptr) {
    t_metadata  *free_meta;

    if (ptr == NULL)
        return ;
    // pthread_mutex_lock(&memory);
    free_meta = (t_metadata *)(ptr - sizeof(t_metadata));
    if (is_block_freeable((void *)free_meta) == false) {
        printf("Error: block cannot be freed.\n");
        // pthread_mutex_unlock(&memory);
        return ;
    }
    free_meta->is_malloc = false;
    if (is_block_free(free_meta->next) == true)
        defragment((void *)free_meta, free_meta->next);
    if (is_block_free(free_meta->prev) == true) {
        free_meta = (t_metadata *)free_meta->prev;
        defragment(free_meta, free_meta->next);
    }
    free_arena_if_empty(free_meta);
    // pthread_mutex_unlock(&memory);
}

void    defragment(void *first_block, void *second_block) {
    t_metadata  *first_meta;
    t_metadata  *second_meta;

    first_meta = (t_metadata *)first_block;
    second_meta = (t_metadata *)second_block;
    set_metadata(first_block, first_meta->size + second_meta->size, first_meta->prev, second_meta->next, false);
    if (second_meta->next != NULL)
        set_metadata(second_meta->next, ((t_metadata *)second_meta->next)->size, first_block, ((t_metadata *)second_meta->next)->next, true);
}

bool    is_block_free(void *block) {
    return (block != NULL && ((t_metadata *)block)->is_malloc == false);
}

void    free_arena_if_empty(t_metadata *free_meta) {
    t_arena *curr_arena;

    if (free_meta->prev == NULL && free_meta->next == NULL) {
        curr_arena = allocated_pages->arenas;
        if (curr_arena->addr == free_meta) {
            allocated_pages->arenas = allocated_pages->arenas->next;
        }
        else {
            while (curr_arena->next->addr != free_meta) {
                write(1, "f", 1);
                curr_arena = curr_arena->next;
            }
            curr_arena->next = curr_arena->next->next;
        }
        munmap(free_meta, free_meta->size);
        if (allocated_pages->arenas == NULL) {
            munmap(allocated_pages, allocated_pages->mmap_size);
            allocated_pages = NULL;
        }
    }
}

bool    is_block_freeable(void *meta_addr) {
    t_arena     *curr_arena;
    t_metadata  *curr_meta;

    if (allocated_pages == NULL || allocated_pages->arenas == NULL)
        return false;
    curr_arena = allocated_pages->arenas;
    while (curr_arena != NULL && (curr_arena->addr > meta_addr || curr_arena->addr + curr_arena->size <= meta_addr)) {
        write(1, "go", 2);
        curr_arena = curr_arena->next;
    }
    if (curr_arena == NULL)
        return false;
    curr_meta = (t_metadata *)curr_arena;
    while (curr_meta != NULL) {
        write(1, "h", 1);
        if ((void *)curr_meta == meta_addr)
            return (curr_meta->is_malloc);
        curr_meta = (t_metadata *)(curr_meta->next);
    }
    return false;
}
