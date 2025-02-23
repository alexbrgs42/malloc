#include "../include/malloc.h"

t_allocs        *arenas = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;

// order arenas by increasing order
// calloc - should decomment overflow protection
// print last free zone that is less than 32 bytes and change next = NULL if realloc again (increase or decrease) or freed
// what size should I mmap for arenas global var ?
// Remove ft_
// NOT RETURN BEFORE MUTEX UNLOCK

int main() {

    void *a = ft_calloc(42, 10);
    void *b = ft_calloc(84, 1);
    void *c = ft_calloc(70, 1);
    void *d = ft_calloc(100, 1);
    void *e = ft_calloc(110, 1);
    void *f = ft_calloc(125, 1);
    show_alloc_mem();
    printf("\n\n");
    void *g = ft_realloc(f, 15786);
    /*e = ft_malloc(110);*/

    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)g;

    show_alloc_mem();
    printf("\n\n");

    g = ft_realloc(f, 100);
    ft_free(b);

    ft_free(c);

    ft_free(a);
    ft_free(b);
    ft_free(c);

    show_alloc_mem();
    printf("\n\n");

    ft_free(d);
    ft_free(e);

    show_alloc_mem();
    printf("\n\n");

    ft_free(f);
    ft_free(g);

    show_alloc_mem();
    printf("\n\n");

    a = ft_malloc(42);
    b = ft_malloc(84);
    c = ft_malloc(70);

    ft_free(a);
    ft_free(b);

    a = ft_malloc(110);
    
    show_alloc_mem();

    return 0;
}
