#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <inttypes.h>
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
# define M 96 * sysconf(_SC_PAGESIZE)

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

typedef struct s_metadata       t_metadata;
typedef struct s_allocs         t_allocs;
typedef struct s_arena          t_arena;

struct s_allocs {
    t_arena *arenas;
    size_t  mmap_size;
};

struct s_arena {
    t_type  type;
    size_t  size;
    void    *addr;
    t_arena *next;
};

struct s_metadata {
    size_t  size;
    void    *prev;
    void    *next;
    bool    is_malloc;
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
bool    is_block_free(void *block);
void    defragment(void *first_block, void *second_block);
void    *ft_malloc(size_t size);
void    mark_block(void *ptr, size_t allocated_size);
void    *tiny_allocation(size_t allocated_size);
void    *small_allocation(size_t allocated_size);
void    *large_allocation(size_t allocated_size);
void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc);

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
void    print_metadata(void *ptr);
char    *get_arena_text_type(t_arena *arena);
void    print_arena_info(t_arena *arena);
size_t  print_allocs_in_arena(void *arena);

#endif
