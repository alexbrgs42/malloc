# include "../include/malloc.h"

t_allocs        *allocated_pages = NULL;
pthread_mutex_t memory = PTHREAD_MUTEX_INITIALIZER;
