#include "../include/malloc.h"

int main() {

    char *a = malloc(10);
    int *b = calloc(20, 10);

    ft_memset(a, 'h', 10);
    a[1] = 25;
    b[0] = 10;

    ft_printf("First show_alloc_mem():\n----------------------\n");
    show_alloc_mem();

    ft_printf("\n\n");
    ft_printf("First show_alloc_mem_ex():\n-------------------------\n");
    show_alloc_mem_ex();

    free(b);

    ft_printf("\n\n");
    ft_printf("Second show_alloc_mem():\n-----------------------\n");
    show_alloc_mem();
    
    free(a);
    
    ft_printf("\n\n");
    ft_printf("Third show_alloc_mem():\n----------------------\n");
    show_alloc_mem();

    return 0;
}
