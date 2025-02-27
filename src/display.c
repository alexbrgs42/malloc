#include "../include/malloc.h"

/// @brief Shows by increasing address order the allocations of each arenas.
void    show_alloc_mem() {
    size_t      total;

    pthread_mutex_lock(&memory);
    if (allocated_pages == NULL || allocated_pages->arenas == NULL) {
        ft_printf("No allocations.\n");
        pthread_mutex_unlock(&memory);
        return ;
    }
    total = show_ordered_arenas();
    ft_printf("Total : %ld bytes\n", total);
    pthread_mutex_unlock(&memory);
}

/// @brief Shows by increasing address order each arenas and their allocations.
/// @return 
int show_ordered_arenas() {
    t_arena    *current;
    t_arena    *ordered;
    t_arena    *smaller;
    t_arena    *last_smaller;
    size_t      total;

    total = 0;
    ordered = allocated_pages->arenas;
    last_smaller = NULL;
    while (ordered != NULL) {
        current = allocated_pages->arenas;
        smaller = allocated_pages->arenas;
        while (current != NULL) {
            if (smaller->addr > current->addr && (last_smaller == NULL || current->addr > last_smaller->addr))
                smaller = current;
            current = current->next;
        }
        show_arena_info(smaller);
        total += show_allocs_in_arena(smaller->addr);
        ordered = ordered->next;
        last_smaller = smaller;
    }
    return total;
}

/// @brief Shows an hexa dump of the allocations.
void    show_alloc_mem_ex() {
    t_arena     *current_arena;
    t_metadata  *current_metadata;

    pthread_mutex_lock(&memory);
    if (allocated_pages == NULL || allocated_pages->arenas == NULL) {
        ft_printf("No allocations.\n");
        pthread_mutex_unlock(&memory);
        return ;
    }
    current_arena = allocated_pages->arenas;
    while (current_arena != NULL) {
        show_arena_info(current_arena);
        current_metadata = current_arena->addr;
        while (current_metadata != NULL) {
            if (current_metadata->is_malloc == true)
                show_hexa_dump_allocated_memory(current_metadata);
            current_metadata = current_metadata->next;
        }
        current_arena = current_arena->next;
        ft_printf("\n");
    }
    pthread_mutex_unlock(&memory);
}

/// @brief Shows the content in hexadecimal of a given pointer. 
/// @param current_metadata 
void    show_hexa_dump_allocated_memory(t_metadata *current_metadata) {
    unsigned char   c;
    char            hexa[16] = "0123456789abcdef";

    ft_printf("\npointer %p -> %p\n-------\n", (void *)current_metadata + sizeof(t_metadata), (void *)current_metadata + current_metadata->size);
    for (size_t i = sizeof(t_metadata); i < current_metadata->size + sizeof(t_metadata); i++) {
        c = ((unsigned char *)current_metadata)[i];
        ft_printf("%c", hexa[c / 16]);
        ft_printf("%c", hexa[c % 16]);
        if (i + 1 != current_metadata->size + sizeof(t_metadata))
            ft_printf("%s", ((i - sizeof(t_metadata) + 1) % 4 == 0 ? "  " : " "));
    }
    ft_printf("\n");
}

/// @brief Shows the informations related to an arena (type and address).
/// @param arena 
void    show_arena_info(t_arena *arena) {
    void    *start;

    start = arena->addr;
    ft_printf("%s : %p\n", get_arena_text_type(arena), start);
}

/// @brief Shows the allocations inside the given arena.
/// @param arena 
/// @return The total number of bytes allocated inside of the arena
/// (without counting the alignment and the metadata).
size_t  show_allocs_in_arena(void *arena) {
    void        *ptr;
    void        *end;
    size_t      total;
    size_t      size;
    t_metadata  *meta;

    total = 0;
    meta = (t_metadata *)arena;
    while (meta != NULL) {
        if (meta->is_malloc == true) {
            size = meta->size;
            ptr = (void *)meta + sizeof(t_metadata);
            end = ptr + meta->size;
            ft_printf("%p - %p : %ld bytes\n", ptr, end, size);
            total += size;
        }
        meta = (t_metadata *)(meta->next);
    }
    return total;
}
