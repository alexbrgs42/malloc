#include "../include/malloc.h"

int main() {

    void *a = malloc(100);
    void *b = malloc(57);

    ft_printf("First show_alloc_mem():\n----------------------\n");
    show_alloc_mem();
    
    free(a);
    a = malloc(5);
    
    ft_printf("\n\n");
    ft_printf("Second show_alloc_mem():\n-----------------------\n");
    show_alloc_mem();

    free(a);
    free(b);

    return 0;
}
