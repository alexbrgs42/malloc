#include "../include/malloc.h"

void    show_alloc_mem() {

    pthread_mutex_lock(&memory);
    printf("hello\n");
    pthread_mutex_unlock(&memory);
    // MANDATORY - VISUAL STATE OF ALLOCATIONS IN EACH AREA BY INCREASING ADDRESSES
}

void    show_alloc_mem_ex() {

    pthread_mutex_lock(&memory);
    printf("hello\n");
    pthread_mutex_unlock(&memory);
    // BONUS - history of allocations, or an hexa dump of the allocated zones
}
