# include "../include/malloc.h"

void  *create_arena(t_type type, size_t size) {
    void    *addr;
    int     ret;
    
    addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (addr == MAP_FAILED) {
        ft_printf("Error: mmap syscall failed.\n");
        return NULL;
    }
    ret = add_arena_to_allocated_pages(addr, type, size);
    if (ret == EXIT_FAILURE)
        return NULL;
    set_metadata((t_metadata *)addr, size, NULL, NULL, false);
    return addr;
}

int add_arena_to_allocated_pages(void *addr, t_type type, size_t size) {
    int      ret;
    t_arena *new_arena;
    t_arena *last_arena;

    new_arena = (t_arena *)((void *)allocated_pages + sizeof(t_allocs));
    last_arena = allocated_pages->arenas;
    if (last_arena != NULL) {
        last_arena = get_last_arena();
        new_arena = (t_arena *)((void *)last_arena + sizeof(t_arena));
        if ((void *)new_arena + sizeof(t_arena) > (void *)allocated_pages + allocated_pages->mmap_size) {
            ret = resize_allocated_pages();
            if (ret == EXIT_FAILURE)
                return EXIT_FAILURE;
            last_arena = get_last_arena();
            new_arena = (t_arena *)((void *)last_arena + sizeof(t_arena));
        }
    }
    new_arena->type = type;
    new_arena->addr = addr;
    new_arena->size = size;
    new_arena->next = NULL;
    if (allocated_pages->arenas == NULL)
        allocated_pages->arenas = new_arena;
    else {
        last_arena->next = new_arena;
        // insert_arena_in_list(new_arena);
    }
    return EXIT_SUCCESS;
}

void    insert_arena_in_list(t_arena *new_arena) {
    t_arena *prev_arena;

    prev_arena = allocated_pages->arenas;
    if (prev_arena->addr > new_arena->addr) {
        new_arena->next = prev_arena;
        allocated_pages->arenas = new_arena;
        return ;
    }
    while (prev_arena->next != NULL && prev_arena->next->addr < new_arena->addr) {
        prev_arena = prev_arena->next;
    }
    if (prev_arena->next == NULL) {
        prev_arena->next = new_arena;
        new_arena->next = NULL;
    }
    else {
        new_arena->next = prev_arena->next;
        prev_arena->next = new_arena;
    }
}

char    *get_arena_text_type(t_arena *arena) {
    t_type  type;

    type = arena->type;
    switch (type) {
        case TINY:
            return "TINY";
        case SMALL:
            return "SMALL";
        default:
            return "LARGE";
    }
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

/// @brief Get last arena of the linked list. There must be at least one arena.
/// @return The lst arena of the linked list.
t_arena *get_last_arena() {
    t_arena *last_arena;

    last_arena = allocated_pages->arenas;
    while (last_arena->next != NULL) {
        last_arena = last_arena->next;
    }
    return last_arena;
}
