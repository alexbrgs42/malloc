# include "malloc.h"

int main() {
    int N = 8;

    int *ptr = mmap(NULL, N * sizeof(int), PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
    if (ptr == MAP_FAILED)
        return 1;
    for (int i = 5; i < 5 + N; i++)
        ptr[i - 5] = i;
    
    for (int i = 0; i < N; i++)
        printf("%d%s", ptr[i], (i == 7 ? "\n" : ", "));
    int ret = munmap((void *)ptr, N);
    if (ret == -1)
        return 1;
    return 0;
}

/*
PROT_READ       -> access for reading

PROT_WRITE       -> access for writing

MAP_ANONYMOUS   -> flag used to create an anonymous mapping.
                 It means the mapping isn't connected to any files.
                 This mapping is used as the basic primitive to extend the heap.

MAP_FIXED       -> flag used to force the system to use the exact mapping address 
                   in the address. If this is not possible, then the mapping will be failed.

MAP_PRIVATE     -> flag meaning the mapping will not be seen by any other processes,
                   and the changes made will not be written to the file.
*/

// source : https://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf
