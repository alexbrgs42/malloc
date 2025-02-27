#include "../include/malloc.h"

/// @brief Find the position of the block that should be allocated.
/// @param block_size The total size that should be allocated.
/// @param type The type of arena that should contain the block (TINY|SMALL|LARGE).
/// @return The address where the allocation should be performed.
void  *get_block(size_t block_size, t_type type) {
    void  *best;

    best = NULL;
    if (allocated_pages == NULL) {
        create_allocated_pages(sizeof(t_allocs *) + 300 * sizeof(t_arena));
        if (allocated_pages == NULL)
            return NULL;
    }
    if (allocated_pages->arenas != NULL) {
        best = best_fit(block_size, type);
    }
    if (best == NULL) {
        best = create_arena(type, get_arena_size_with_block(block_size));
    }
    return best;
}

/// @brief The best fit alogorithm searches for the smallest block in which the 
/// requested allocation can fit (i.e. the best one).
/// @param block_size The total size that should be allocated.
/// @param type The type of arena that should contain the block (TINY|SMALL|LARGE).
/// @return The address where the allocation should be performed.
void  *best_fit(size_t block_size, t_type type) {
    void    *head;
    void    *best;
    t_arena *arena;

    best = NULL;
    arena = allocated_pages->arenas;
    while (arena != NULL) {
        if (arena->type == type) {
            head = arena->addr;
            while (head != NULL && arena->addr + arena->size > head + sizeof(t_metadata)) {
                if ((((t_metadata *)head)->is_malloc) == false && get_block_size(head) >= block_size
                    && (best == NULL || get_block_size(head) < get_block_size(best))) {
                    best = head;
                }
                head = ((t_metadata *)head)->next;
            }
        }
        arena = arena->next;
    }
    return best;
}
