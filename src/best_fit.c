#include "../include/malloc.h"

void  *get_block(size_t size, t_type type) {
    void  *best;

    best = NULL;
    if (allocated_pages == NULL) {
        create_allocated_pages(sizeof(t_allocs *) + 100 * sizeof(t_arena));
        if (allocated_pages == NULL)
            return NULL;
    }
    if (allocated_pages->arenas != NULL) {
        best = best_fit(size, type);
    }
    // No arena or arenas full
    if (best == NULL) {
        best = create_arena(type, get_arena_size_with_block(size));
    }
    return best;
}

void  *best_fit(size_t size, t_type type) {
    void    *head;
    void    *best;
    t_arena *curr_arena;

    best = NULL;
    curr_arena = allocated_pages->arenas;
    while (curr_arena != NULL) {
        if (curr_arena->type == type) {
            head = curr_arena->addr;
            while (head != NULL) {
                if ((((t_metadata *)head)->is_malloc) == false && ((t_metadata *)head)->size >= size && (best == NULL || ((t_metadata *)head)->size < ((t_metadata *)best)->size)) {
                    best = head;
                }
                head = ((t_metadata *)head)->next;
            }
        }
        curr_arena = curr_arena->next;
    }
    return best;
}
