#ifndef MALLOC_H
# define MALLOC_H

# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/mman.h>

#define ALIGNMENT 8 // must be a multiple of 2
#define ALIGN(size) ((size + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

#endif