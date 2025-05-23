#include "../include/malloc.h"

int main() {

    void *a = malloc(10);
    void *g = realloc(a, 999999999);
    
    ft_printf("First show_alloc_mem():\n----------------------\n");
    show_alloc_mem();

    ft_printf("\n");

    free(a);
    free(g);

    ft_printf("\n");
    ft_printf("Second show_alloc_mem():\n-----------------------\n");
    show_alloc_mem();

    return 0;
}
