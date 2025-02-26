#include "../include/malloc.h"

void    show_alloc_mem() {
    size_t      total;
    t_arena     *current_arena;

    pthread_mutex_lock(&memory);
    if (allocated_pages == NULL || allocated_pages->arenas == NULL) {
        ft_printf("No allocations.\n");
        pthread_mutex_unlock(&memory);
        return ;
    }
    total = 0;
    current_arena = allocated_pages->arenas;
    while (current_arena != NULL) {
        show_arena_info(current_arena);
        total += show_allocs_in_arena(current_arena->addr);
        current_arena = current_arena->next;
    }
    ft_printf("Total : %d bytes\n", total);
    pthread_mutex_unlock(&memory);
}

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

void    show_hexa_dump_allocated_memory(t_metadata *current_metadata) {
    unsigned char   c;
    char            hexa[16] = "0123456789abcdef";

    ft_printf("\npointer %p -> %p\n-------\n", (void *)current_metadata + sizeof(t_metadata), (void *)current_metadata + current_metadata->size);
    for (size_t i = sizeof(t_metadata); i < current_metadata->size; i++) {
        c = ((unsigned char *)current_metadata)[i];
        ft_printf("%c", hexa[c / 16]);
        ft_printf("%c", hexa[c % 16]);
        if (i + 1 != current_metadata->size)
            ft_printf("%s", ((i - sizeof(t_metadata) + 1) % 4 == 0 ? "  " : " "));
    }
    ft_printf("\n");
}

void    show_metadata(void *ptr) {
    t_metadata  *meta;
    char        *format;

    if (ptr == NULL)
        return ;
    meta = (t_metadata *)(ptr - sizeof(t_metadata));
    format = "METADATA\n--------\naddress: %p\nsize = %d\nprev = %p\nnext = %p\nis allocated = %s\n\n";
    while (meta != NULL) {
        ft_printf(format, meta, meta->size, meta->prev, meta->next, (meta->is_malloc ? "true" : "false"));
        meta = (t_metadata *)meta->next;
    }
}

void    show_arena_info(t_arena *arena) {
    void    *start;
    void    *end;

    start = arena->addr;
    end = arena->addr + arena->size;
    ft_printf("%s : %p -> %p\n", get_arena_text_type(arena), (uintptr_t)start, (uintptr_t)end);
}

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
            size = meta->size - sizeof(t_metadata);
            ptr = (void *)meta + sizeof(t_metadata);
            end = (void *)meta + meta->size;
            ft_printf("malloc - %p - %p : %d bytes\n", (uintptr_t)ptr, (uintptr_t)end, size);
            total += size;
        }
        else {
            size = meta->size;
            ptr = (void *)meta;
            end = (void *)meta + meta->size;
            ft_printf("free   - %p - %p : %d bytes\n", (uintptr_t)ptr, (uintptr_t)end, size);
        }
        meta = (t_metadata *)(meta->next);
    }
    return total;
}
