#include "../include/malloc.h"

void    show_alloc_mem() {
    size_t      total = 0;
    t_arena     *current_arena;

    pthread_mutex_lock(&memory);
    if (arenas == NULL || arenas->arenas == NULL) {
        printf("No allocations.\n");
        pthread_mutex_unlock(&memory);
        return ;
    }
    current_arena = arenas->arenas;
    while (current_arena != NULL) {
        show_arena_info(current_arena);
        total += show_allocs_in_arena(current_arena->addr);
        current_arena = current_arena->next;
    }
    printf("Total : %ld bytes\n", total);
    pthread_mutex_unlock(&memory);
}

void    show_alloc_mem_ex() {
    pthread_mutex_lock(&memory);
    printf("hello\n");
    pthread_mutex_unlock(&memory);
    // BONUS - history of allocations, or an hexa dump of the allocated zones
}

void    show_metadata(void *ptr) {
    t_metadata  *meta;
    char        *format;

    if (ptr == NULL)
        return ;
    meta = (t_metadata *)(ptr - sizeof(t_metadata));
    format = "METADATA\n--------\naddress: 0x%lX\nsize = %ld\nprev = %s%lX\nnext = %s%lX\nis allocated = %s\n\n";
    while (meta != NULL) {
        printf(format, (uintptr_t)meta, meta->size, (meta->prev == NULL ? "": "0x"), (uintptr_t)meta->prev, (meta->next == NULL ? "": "0x"), (uintptr_t)meta->next, (meta->is_malloc ? "true" : "false"));
        meta = (t_metadata *)meta->next;
    }
}

void    show_arena_info(t_arena *arena) {
    void    *start = arena->addr;
    // void    *end = start + arena->size;

    printf("%s : 0x%lX\n", get_arena_text_type(arena), (uintptr_t)start);
}

size_t  show_allocs_in_arena(void *arena) {
    t_metadata  *meta = (t_metadata *)arena;
    size_t      total = 0;
    size_t      size = 0;
    void        *ptr = NULL;
    void        *end = NULL;

    while (meta != NULL) {
        if (meta->is_malloc == true) {
            size = meta->size - sizeof(t_metadata);
            ptr = (void *)meta + sizeof(t_metadata);
            end = (void *)meta + meta->size;
            printf("malloc - 0x%lX - 0x%lX : %ld bytes\n", (uintptr_t)ptr, (uintptr_t)end, size);
            total += size;
        }
        else {
            size = meta->size;
            ptr = (void *)meta;
            end = (void *)meta + meta->size;
            printf("free   - 0x%lX - 0x%lX : %ld bytes\n", (uintptr_t)ptr, (uintptr_t)end, size);
        }
        meta = (t_metadata *)(meta->next);
    }
    return total;
}
