#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/mman.h>
# include "../libft/include/libft.h"

// #################################################################
// #                                                               #
// #                            DEFINES                            #
// #                                                               #
// #################################################################

#define ALIGNMENT 8
#define ALIGN(size) ((size + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

// #################################################################
// #                                                               #
// #                          STRUCTURES                           #
// #                                                               #
// #################################################################

typedef struct s_free_historic  t_free_historic;
typedef struct s_allocs         t_allocs;
typedef struct s_metadata       t_metadata;

struct s_allocs {
    uint32_t        tiny_arena;
    uint32_t        small_arena;
    t_free_historic *head;
};

struct s_free_historic {
    uint32_t        addr;
    size_t          size;
    t_free_historic *next;
};

struct s_metadata {
    size_t      size;
    uint32_t    prev;
    uint32_t    next;
};

// #################################################################
// #                                                               #
// #                            GLOBALS                            #
// #                                                               #
// #################################################################

extern t_allocs alloc_table;

#endif
