# include "../include/malloc.h"

/// @brief Allocates the global structure and initialize it for the first allocation.
/// @param mmap_size The initial size of the mmap.
void    create_allocated_pages(size_t mmap_size) {
    allocated_pages = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (allocated_pages == MAP_FAILED) {
        allocated_pages = NULL;
        ft_printf("Error: mmap syscall failed.\n");
        return ;
    }
    allocated_pages->arenas = NULL;
    allocated_pages->mmap_size = mmap_size;
}

/// @brief Increase the size of the global structureby a fixed size.
/// @return mmap return status.
int resize_allocated_pages() {
    size_t      mmap_size;
    t_allocs    *old_allocated_pages;

    old_allocated_pages = allocated_pages;
    mmap_size = allocated_pages->mmap_size + 100 * sizeof(t_arena);
    create_allocated_pages(mmap_size);
    if (allocated_pages == NULL)
        return EXIT_FAILURE;
    copy_allocated_pages_content(old_allocated_pages);
    munmap(old_allocated_pages, old_allocated_pages->mmap_size);
    return EXIT_SUCCESS;
}

/// @brief Copies the content of the global structure to the 
/// bigger new one by adding each arenas one by one.
/// @param old_allocated_pages Old global structure.
void    copy_allocated_pages_content(t_allocs *old_allocated_pages) {
    t_arena *curr;

    curr = old_allocated_pages->arenas;
    while (curr != NULL) {
        add_arena_to_allocated_pages(curr->addr, curr->type, curr->size);
        curr = curr->next;
    }
}
