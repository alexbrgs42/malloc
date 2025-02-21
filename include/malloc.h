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

# define FREE_BLOCK(size) (size & ~1UL)
# define ABSOLUT_SIZE(size) (size & ~1UL)
# define USED_BLOCK(size) (size | 1)

# define N 4 * sysconf(_SC_PAGESIZE) 
# define M 32 * sysconf(_SC_PAGESIZE) 

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
    void    *addr;
    t_arena *next;
};

struct s_free_historic {
    t_type          type;
    size_t          size;
    void            *addr;
    t_free_historic *next;
};

struct s_metadata {
    size_t  size;
    void    *prev;
    void    *next;
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
void    mark_block(void *ptr, size_t size);
void    *tiny_allocation(size_t size);
void    *small_allocation(size_t size);
void    *large_allocation(size_t size);
void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next);
size_t  get_block_aligned_size(void *ptr);

// best_fit.c
void  *get_block(size_t size, t_type type);
void  *best_fit(size_t size, t_type type);
void  *create_arena(t_type type, size_t size);
size_t  get_arena_size_with_block(size_t blk_size);
void    add_arena(void *addr, t_type type, size_t size);
t_arena *get_last_arena();

// display.c
void    show_alloc_mem();
void    show_alloc_mem_ex();

#endif
