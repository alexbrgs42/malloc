#include "../include/malloc.h"

// remove unnecessary in display.c
// order in arena adresses (infinite loop) -> should handle it in print functions
// print real size
// add size_t for ft_printf


// gcc tests/main1.c -I./include -Llibft -lft -lft_malloc -L./ -o executable

// LD_PRELOAD="./libft_malloc.so" /usr/bin/time -v /bin/ls

// in gdb 
// set exec-wrapper env 'LD_LIBRARY_PATH=.' 'LD_PRELOAD=libft_malloc.so'
// then run

int main() {

    char *a = malloc(10);
    char *b = malloc(102);
    b = malloc(6666666668);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);
    b = malloc(1202);

    ft_memset(a, '\n', 10);

    (void)a;
    (void)b;

    show_alloc_mem();

    return 0;
}
