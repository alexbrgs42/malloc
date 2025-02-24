#include "../include/malloc.h"

void    *calloc(size_t nmemb, size_t size) {
    void    *ptr;

    // pthread_mutex_lock(&memory);
    if (nmemb * size == 0) {
        // pthread_mutex_unlock(&memory);
        return NULL;
    }
    // condition suffisante ?
    if (nmemb * size < nmemb || nmemb * size < size) {
        // pthread_mutex_unlock(&memory);
        return NULL;
    }
    // pthread_mutex_unlock(&memory);
    ptr = malloc(nmemb * size);
    if (ptr == NULL)
        return NULL;
    // pthread_mutex_lock(&memory);
    ft_bzero(ptr, nmemb * size);
    // pthread_mutex_unlock(&memory);
    return ptr;
}
