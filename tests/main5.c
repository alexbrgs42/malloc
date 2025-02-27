#include "../include/malloc.h"

int main() {

    void *a = malloc(42);
    void *b = malloc(84);
    void *c = malloc(3725);
    void *d = malloc(48847);

    ft_printf("First show_alloc_mem():\n----------------------\n");
    show_alloc_mem();

    free(a);
    free(b);
    free(c);
    free(d);

    return 0;
}
