#include "malloc.h"

// 1 global for alllocation management and 1 for thread safety

void    *realloc(void *ptr, size_t size) {

    // ...?
}

void    free(void *ptr) {

    // TEST FOR NULL

    // CHANGE BIT

    // DOESN'T FREE IF ALLOC REMAINS IN TINY OR SMALL

    // COALESCING (DEFRAGMENTATION)
}

void    *malloc(size_t size) {

    // TINY

    // SMALL

    // LARGE

    // TOO BIG
}

void    *tiny_allocation(size_t size) {

    // STATIC VAR FOR FIRST TIME ?

    // ALLOCATE ENTIRE SPACE IF NOT

    // BEST FIT (if no space, best fit on small and if still no space, mmap on large area)

    // MARK FIRST BIT

    // KEEP TRACK OF FREE SPACES

    // ...?
}

void    *small_allocation(size_t size) {

    // STATIC VAR FOR FIRST TIME ?

    // ALLOCATE ENTIRE SPACE IF NOT

    // BEST FIT (if no space, mmap on large area)

    // MARK FIRST BIT

    // KEEP TRACK OF FREE SPACES

    // ...?
}

void    *large_allocation(size_t size) {

    // MAX SIZE ?

    // MMAP

    // MARK FIRST BIT
}

void    *best_fit(uint32_t head, uint32_t tail, size_t alloc_size) {

    // SEARCHES FOR BEST FIT ON THE TINY OR SMALL AREAS

    // RETURNS START ADDRESS OF BEST FIT (enum in case of error - no space left, ...)
}

void    show_alloc_mem() {

    // MANDATORY - VISUAL STATE OF ALLOCATIONS IN EACH AREA BY INCREASING ADDRESSES
}

void    show_alloc_mem_ex() {

    // BONUS - history of allocations, or an hexa dump of the allocated zones
}

// DO MULTI-THREAD SAFETY
// MANAGE MALLOC DEBUG ENVIRONMENT VARIABLES