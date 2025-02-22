#include "../include/malloc.h"

t_allocs        *arenas = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;

// realloc
// calloc
// what size should I mmap for arenas global var ?
// Remove ft_
// NOT RETURN BEFORE MUTEX UNLOCK

int main() {
    void *a = ft_malloc(42);
    void *b = ft_malloc(84);
    void *c = ft_malloc(70);
    void *d = ft_malloc(100);
    void *e = ft_malloc(110);
    void *f = ft_malloc(3725);
    void *g = ft_malloc(48847);

    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)g;

    show_alloc_mem();
    ft_free(b);

    ft_free(c);

    ft_free(a);
    ft_free(b);
    ft_free(c);

    show_alloc_mem();

    ft_free(d);
    ft_free(e);

    show_alloc_mem();

    ft_free(f);
    ft_free(g);

    show_alloc_mem();

    a = ft_malloc(42);
    b = ft_malloc(84);
    c = ft_malloc(70);

    ft_free(a);
    ft_free(b);

    a = ft_malloc(110);
    
    show_alloc_mem();

    return 0;
}
