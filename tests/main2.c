#include "../include/malloc.h"

// calloc - should decomment overflow protection
// print last free zone that is less than 32 bytes and change next = NULL if realloc again (increase or decrease) or freed
// Remove ft_
// do show_alloc_mem_ex()
// remettre ft_calloc libft ?

int main() {

    void *a = malloc(10);
    void *g = realloc(a, 392764 + 420 - 10);

    free(a);
    (void)g;

    return 0;
}
