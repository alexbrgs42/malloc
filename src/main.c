#include "../include/malloc.h"

t_allocs        *arenas = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;

// size is ALIGN(size + sizeof(t_metadata)), real size not available.
// PATCH: next is not NULL but should be

int main() {

    size_t *a = ft_malloc(10);
    printf("%p\n", a - sizeof(t_metadata));

    void *tp_a = (void *)(a - sizeof(t_metadata));
    t_metadata *m = (t_metadata *)tp_a;
    printf("a->next = %p, a->prev = %p, a->size = %ld\n", m->next, m->prev, m->size - sizeof(t_metadata));

    // arenas = mmap(NULL, sizeof(t_allocs *), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // if (arenas == MAP_FAILED) {
    //     printf("Error with mmap syscall.\n");
    //     return 1;
    // }
    // arenas->arenas = NULL;
    // arenas->frees = NULL;

    // size_t *blk = mmap(NULL, N, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // add_arena(blk, TINY);

    // size_t *blk2 = mmap(NULL, M, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // add_arena(blk2, SMALL);

    t_arena *tmp = arenas->arenas;
    printf("arena: blk = %p, addr = %p, type = %s, next = %p\n", tmp, tmp->addr, (tmp->type == 0 ? "TINY" : (tmp->type == 1 ? "SMALL" : "LARGE")), tmp->next);
    // tmp = tmp->next;
    // printf("arena: blk = %p, addr = %p, type = %s, next = %p\n", blk2, tmp->addr, (tmp->type == 0 ? "TINY" : (tmp->type == 1 ? "SMALL" : "LARGE")), tmp->next);

    return 0;
}
