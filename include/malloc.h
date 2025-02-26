#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>
# include <unistd.h>
// # include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <inttypes.h>
# include <pthread.h>
# include <sys/mman.h>
# include "../libft/include/libft.h"
# include "../ft_printf/ft_printf.h"

// #################################################################
// #                                                               #
// #                            DEFINES                            #
// #                                                               #
// #################################################################

# define ALIGNMENT 8
# define ALIGN(size) ((size + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

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

extern t_allocs         *allocated_pages;
extern pthread_mutex_t  memory;

// #################################################################
// #                                                               #
// #                           FUNCTIONS                           #
// #                                                               #
// #################################################################

// malloc.c
void    *malloc(size_t size);
void    *tiny_small_allocation(size_t allocated_size, t_type type);
void    *large_allocation(size_t allocated_size);

// free.c
void    free(void *ptr);
void    defragment(void *first_block, void *second_block);
bool    is_block_free(void *block);
void    free_arena_if_empty(t_metadata *free_meta);
bool    is_block_freeable(void *meta_addr);

// realloc.c
void    *realloc(void *ptr, size_t size);
void    *increase_realloc_at_different_address(void *ptr, size_t size);
void    fill_reallocated_block(void *new_ptr, void *ptr);
size_t  available_size_for_realloc(t_metadata *meta);
void    increase_realloc_at_same_address(void *ptr, size_t size);
void    decrease_realloc(void *ptr, size_t size);

// calloc.c
void    *calloc(size_t nmemb, size_t size);

// metadata.c
void    mark_block(void *ptr, size_t allocated_size);
void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc);

// best_fit.c
void  *get_block(size_t size, t_type type);
void  *best_fit(size_t size, t_type type);

// allocated_pages.c
void    create_allocated_pages(size_t mmap_size);
int     resize_allocated_pages();
void    copy_allocated_pages_content(t_allocs *old_allocated_pages);

// new_arena.c
void    *create_arena(t_type type, size_t size);
int     add_arena_to_allocated_pages(void *addr, t_type type, size_t size);
char    *get_arena_text_type(t_arena *arena);
size_t  get_arena_size_with_block(size_t blk_size);
t_arena *get_last_arena();

// display.c
void    show_alloc_mem();
void    show_alloc_mem_ex();
void    show_metadata(void *ptr);
void    show_hexa_dump_allocated_memory(t_metadata *current_metadata);
void    show_arena_info(t_arena *arena);
size_t  show_allocs_in_arena(void *arena);

#endif
