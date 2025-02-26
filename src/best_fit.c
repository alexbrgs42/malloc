#include "../include/malloc.h"

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
    // No arena or arenas full
    if (best == NULL) {
        best = create_arena(type, get_arena_size_with_block(block_size));
    }
    return best;
}

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

size_t  get_block_size(t_metadata *meta) {
    t_arena *arena;

    if (meta->next == NULL) {
        arena = get_arena_of_block(meta);
        if (arena == NULL)
            return 0;
        return (size_t)(arena->addr + arena->size - (void *)meta);
    }
    return (size_t)(meta->next - (void *)meta);
}

t_arena *get_arena_of_block(t_metadata *meta) {
    t_arena    *arena;

    if (allocated_pages == NULL)
        return NULL;
    arena = allocated_pages->arenas;
    while (arena != NULL) {
        if ((void *)meta >= arena->addr && (void *)meta < arena->addr + arena->size)
            return arena;
        arena = arena->next;
    }
    return NULL;
}