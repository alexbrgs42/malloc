#include "../include/malloc.h"

char    *get_arena_text_type(t_arena *arena) {
    t_type t = arena->type;

    switch (t) {
        case TINY:
            return "TINY";
        case SMALL:
            return "SMALL";
        default:
            return "LARGE";
    }
}

void    show_alloc_mem() {
    t_arena     *current_arena;
    t_metadata  *meta;
    size_t      total = 0;

    pthread_mutex_lock(&memory);
    if (arenas == NULL || arenas->arenas == NULL) {
        printf("No allocations.\n");
        return ;
    }
    current_arena = arenas->arenas;
    while (current_arena != NULL) {
        printf("%s : %p - %p\n", get_arena_text_type(current_arena), current_arena->addr, current_arena->addr + current_arena->size);
        meta = (t_metadata *)(current_arena->addr);
        while (meta != NULL) {
            if ((meta->size & 1) == 1) {
                printf("%p - %p : %ld bytes\n", meta, (meta->next != NULL ? meta->next - 1 : current_arena->addr + current_arena->size), ABSOLUT_SIZE(meta->size));
                total += ABSOLUT_SIZE(meta->size); // should have real value
            }
            meta = (t_metadata *)(meta->next);
        }
        current_arena = current_arena->next;
    }
    printf("Total : %ld bytes\n", total);
    pthread_mutex_unlock(&memory);
    // MANDATORY - VISUAL STATE OF ALLOCATIONS IN EACH AREA BY INCREASING ADDRESSES
}

void    show_alloc_mem_ex() {

    pthread_mutex_lock(&memory);
    printf("hello\n");
    pthread_mutex_unlock(&memory);
    // BONUS - history of allocations, or an hexa dump of the allocated zones
}
