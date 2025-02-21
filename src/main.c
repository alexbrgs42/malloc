#include "../include/malloc.h"

t_allocs        *arenas = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;

// size is ALIGN(size + sizeof(t_metadata)), real size not available.
// free
// realloc
// calloc
// large_allocation
// verify that used or unused block is maintained with size calculation
// what should I mmap for arenas global var ?
// Remove ft_

// TODO!! - crash if too many large allocations

int main() {

    int i = 0;
    while (i < 100) {
        ft_malloc(42);
        i++;
    }
    ft_malloc(4343);
    // ft_malloc(10000);
    // ft_malloc(10000);
    // ft_malloc(10000);
    // ft_malloc(10000);

    show_alloc_mem();

    return 0;
}
