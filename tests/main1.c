#include "../include/malloc.h"

// print last free zone that is less than 32 bytes and change next = NULL if realloc again (increase or decrease) or freed
// do show_alloc_mem_ex()
// remove write
// remove unnecessary in display.c
// order in arena adresses (infinite loop) -> should handle it in print functions
// crash with vim

// gcc tests/main1.c -I./include -Llibft -lft -lft_malloc -L./ -o executable

// LD_PRELOAD="./libft_malloc.so" /usr/bin/time -v /bin/ls

// in gdb 
// set exec-wrapper env 'LD_LIBRARY_PATH=.' 'LD_PRELOAD=libft_malloc.so'
// then run

int main() {

    ft_printf("%p\n", 0x7ffff7514860 + sizeof(t_metadata));
    // char *a = malloc(10);
    // char *b = malloc(102);
    // b = malloc(1202);

    // ft_memset(a, '\n', 10);

    // (void)a;
    // (void)b;

    // show_alloc_mem_ex();

    return 0;
}
