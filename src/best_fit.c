#include "../include/malloc.h"

void  *get_block(size_t size, t_type type) {

    void  *best = NULL;

    if (arenas == NULL) {
        // bad
        arenas = mmap(NULL, sizeof(t_allocs *), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (arenas == MAP_FAILED) {
            printf("Error with mmap syscall.\n");
            return NULL;
        }
        arenas->arenas = NULL;
        arenas->frees = NULL;
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

    void  *head = NULL;
    void  *best = NULL;
    t_arena *curr_arena = arenas->arenas;

    while (curr_arena != NULL) {
        if (curr_arena->type == type) {
            head = curr_arena->addr;
            while (head != NULL) {
                if ((((t_metadata *)head)->size & 1) == 0 && ((t_metadata *)head)->size >= size && (best == NULL || ((t_metadata *)head)->size < ((t_metadata *)best)->size)) {
                    best = head;
                }
                head = ((t_metadata *)head)->next;
            }
        }
        curr_arena = curr_arena->next;
    }
    return best;
}

void  *create_arena(t_type type, size_t size) {

    void *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (addr == MAP_FAILED)
        return NULL;
    ft_bzero(addr, size);
    add_arena(addr, type, size);
    set_metadata(addr, size, NULL, NULL);
    return addr;
}

size_t  get_arena_size_with_block(size_t blk_size) {
    // TINY
    if (blk_size <= (size_t)(N / 100))
        return (size_t)N;
    // SMALL
    else if (blk_size <= (size_t)(M / 100))
        return (size_t)M;
    // LARGE
    return blk_size;
}

void    add_arena(void *addr, t_type type, size_t size) {
    t_arena *new_arena;
    t_arena *last_arena;
    
    new_arena = (t_arena *)(arenas + sizeof(t_allocs));
    last_arena = arenas->arenas;
    if (last_arena != NULL) {
        last_arena = get_last_arena();
        new_arena = (t_arena *)(last_arena + sizeof(t_arena));
    }
    new_arena->type = type;
    new_arena->addr = addr;
    new_arena->size = size;
    new_arena->next = NULL;
    if (arenas->arenas == NULL)
        arenas->arenas = new_arena;
    else
        last_arena->next = new_arena;
}

/// @brief Get last arena of the linked list. There must be at least one arena.
/// @return The lst arena of the linked list.
t_arena *get_last_arena() {
    t_arena *last_arena;

    last_arena = arenas->arenas;
    while (last_arena->next != NULL)
        last_arena = last_arena->next;
    return last_arena;
}
