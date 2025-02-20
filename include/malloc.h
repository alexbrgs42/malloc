#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/mman.h>
# include "../libft/include/libft.h"

// #################################################################
// #                                                               #
// #                            DEFINES                            #
// #                                                               #
// #################################################################

# define ALIGNMENT 8
# define ALIGN(size) ((size + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

# define FREE_BLOCK(size) size | 0
# define USED_BLOCK(size) size | 1

# define N 4 * getpagesize()
# define M 32 * getpagesize()

// #################################################################
// #                                                               #
// #                             ENUMS                             #
// #                                                               #
// #################################################################

typedef enum e_type t_type;

enum e_type {
    TINY,
    SMALL,
    LARGE,
    NO_TYPE
};

// #################################################################
// #                                                               #
// #                          STRUCTURES                           #
// #                                                               #
// #################################################################

typedef struct s_free_historic  t_free_historic;
typedef struct s_metadata       t_metadata;
typedef struct s_allocs         t_allocs;
typedef struct s_arena          t_arena;

struct s_allocs {
    t_arena         *arenas;
    t_free_historic *frees;
};

struct s_arena {
    t_type  type;
    size_t  size;
    // should change type ?
    size_t  *addr;
    t_arena *next;
};

struct s_free_historic {
    t_type          type;
    size_t          size;
    // should change type ?
    size_t          *addr;
    t_free_historic *next;
};

struct s_metadata {
    size_t      size;
    // should change type ?
    size_t      *prev;
    // should change type ?
    size_t      *next;
};

// #################################################################
// #                                                               #
// #                            GLOBALS                            #
// #                                                               #
// #################################################################

extern t_allocs         *arenas;
extern pthread_mutex_t  memory;

// #################################################################
// #                                                               #
// #                           FUNCTIONS                           #
// #                                                               #
// #################################################################

// allocation.c
void    *ft_realloc(void *ptr, size_t size);
void    ft_free(void *ptr);
void    *ft_malloc(size_t size);
void    *tiny_allocation(size_t size);
void    *small_allocation(size_t size);
void    *large_allocation(size_t size);
void    set_metadata(size_t *ptr, size_t size, size_t *prev, size_t *next);
void    mark_chunk(t_metadata *ptr, size_t size);

// best_fit.c
size_t  *get_block(size_t size, t_type type);
size_t  *best_fit(size_t size, t_type type);
size_t  *create_arena(t_type type, size_t size);
size_t  get_arena_size_with_block(size_t blk_size);
void    add_arena(size_t *addr, t_type type);
t_arena *get_last_arena();

// display.c
void    show_alloc_mem();
void    show_alloc_mem_ex();

#endif
