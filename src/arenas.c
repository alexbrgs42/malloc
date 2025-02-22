# include "../include/malloc.h"

void  *create_arena(t_type type, size_t size) {
    void    *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (addr == MAP_FAILED)
        return NULL;
    ft_bzero(addr, size);
    add_arena(addr, type, size);
    set_metadata(addr, size, NULL, NULL, false);
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
    
    new_arena = (t_arena *)((void *)arenas + sizeof(t_allocs));
    last_arena = arenas->arenas;
    if (last_arena != NULL) {
        last_arena = get_last_arena();
        new_arena = (t_arena *)((void *)last_arena + sizeof(t_arena));
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

char    *get_arena_text_type(t_arena *arena) {
    t_type  t = arena->type;

    switch (t) {
        case TINY:
            return "TINY";
        case SMALL:
            return "SMALL";
        default:
            return "LARGE";
    }
}
