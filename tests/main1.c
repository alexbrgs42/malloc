#include "../include/malloc.h"

// calloc - should decomment overflow protection
// print last free zone that is less than 32 bytes and change next = NULL if realloc again (increase or decrease) or freed
// do show_alloc_mem_ex()
// use ft_printf
// remove write
// order in arena adresses (infinite loop when free etc)
// infinite loop opening code (c) or vim

// LD_PRELOAD="./libft_malloc.so" /usr/bin/time -v /bin/ls

int main() {

    void *a;
    for (int i = 0; i < 200; i++) 
        a = malloc(100);
    // show_alloc_mem();
    write(1, "\n\n", 2);
    void *g = realloc(a, 392764 + 420 - 10);

    (void)a;
    // (void)g;

    free(a);
    show_alloc_mem();

    return 0;
}
