#include "../include/malloc.h"

void  *get_block(size_t size, t_type type) {
    void  *best = NULL;

    if (arenas == NULL) {
        // bad
        // should change mmap_size too
        arenas = mmap(NULL, 100 * sizeof(t_arena *), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (arenas == MAP_FAILED) {
            printf("Error with mmap syscall.\n");
            return NULL;
        }
        arenas->arenas = NULL;
        arenas->mmap_size = 100 * sizeof(t_arena *);
    }

    if (arenas->arenas != NULL) {
        best = best_fit(size, type);
    }

    // No arena or arenas full
    if (best == NULL) {
        best = create_arena(type, get_arena_size_with_block(size));
    }

    return best;
}

void  *best_fit(size_t size, t_type type) {
    void    *head = NULL;
    void    *best = NULL;
    t_arena *curr_arena = arenas->arenas;

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
