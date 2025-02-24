#include "../include/malloc.h"

t_allocs        *allocated_pages = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;

// calloc - should decomment overflow protection
// print last free zone that is less than 32 bytes and change next = NULL if realloc again (increase or decrease) or freed
// Remove ft_
// NOT RETURN BEFORE MUTEX UNLOCK

int main() {

    void *a = ft_calloc(42, 10);
    show_alloc_mem();
    printf("\n\n");
    void *g = ft_realloc(a, 392764 + 420 - 10);

    (void)a;
    (void)g;

    show_alloc_mem();

    return 0;
}
