#include "../include/malloc.h"

int main() {

    void *a = calloc(999999999, 999999999);
    
    (void )a;

    ft_printf("\n");
    ft_printf("First show_alloc_mem():\n----------------------\n");
    show_alloc_mem();

    return 0;
}
