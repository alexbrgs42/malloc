#include "../include/malloc.h"

size_t  *best_fit(size_t size, t_type arena_type) {

    size_t  *head = NULL;
    size_t  *tail = NULL;
    size_t  *best = NULL;
    t_arena *curr_arena = arenas->arenas;

    while (curr_arena->addr != NULL) {
        if (curr_arena->type == arena_type) {
            head = curr_arena->addr;
            tail = head + (arena_type == TINY ? N : M);
            while (head < tail) {
                if ((*head & 1) == 0 && *head >= size && (best == NULL || *head < *best))
                    best = head;
                head = head + *head;
            }
        }
        curr_arena = curr_arena->next;
    }

    if (best == NULL) {
        int ret = create_arena(curr_arena, arena_type);
        if (ret == EXIT_FAILURE)
            return NULL;
        return curr_arena->addr;
    }

    return best;
}

// add { NO_TYPE, NULL, NULL} to new next
void    empty_arena(t_arena *empty_a) {
    t_arena a;

    a.addr = NULL;
    a.next = NULL;
    a.type = NO_TYPE;
    *empty_a = a;
}

int create_arena(t_arena *new_arena, t_type arena_type) {
    new_arena->addr = mmap(NULL, (arena_type == TINY ? N : M), PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    if (new_arena->addr == MAP_FAILED)
        return EXIT_FAILURE;
    new_arena->type = arena_type;
    empty_arena(new_arena->next);
    set_metadata(new_arena->addr, (arena_type == TINY ? FREE_BLOCK(N) : FREE_BLOCK(M)), NULL, NULL);
    return EXIT_SUCCESS;
}
