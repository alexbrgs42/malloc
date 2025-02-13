# include "../include/malloc.h"

t_allocs        *arenas = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;

int main() {

    return 0;
}

// NOT COALESCE BETWEEN TINY AND SMALL