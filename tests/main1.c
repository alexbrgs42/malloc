#include "../include/malloc.h"

// verify display.c
// replace size with get_block_size and store real size instead


// gcc tests/main1.c -I./include -Llibft -lft -lft_malloc -L./ -o executable

// LD_PRELOAD="./libft_malloc.so" /usr/bin/time -v /bin/ls

// in gdb 
// set exec-wrapper env 'LD_LIBRARY_PATH=.' 'LD_PRELOAD=libft_malloc.so'
// then run

int main() {

    char *a = malloc(10);
    char *b = malloc(102);
    b = malloc(66666);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    a = malloc(12);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    b = malloc(12);
    free(a);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);
    b = malloc(18);

    ft_memset(a, '\n', 10);

    (void)a;
    (void)b;

    show_alloc_mem();

    ft_printf("\n\n");

    ft_printf("%ld\n", get_block_size((void *)b - sizeof(t_metadata)));

    // show_alloc_mem_ex();

    return 0;
}
