# include "../include/malloc.h"

void    create_allocated_pages(size_t mmap_size) {
    allocated_pages = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (allocated_pages == MAP_FAILED) {
        allocated_pages = NULL;
        printf("Error: mmap syscall failed.\n");
        return ;
    }
    allocated_pages->arenas = NULL;
    allocated_pages->mmap_size = mmap_size;
}

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

void    copy_allocated_pages_content(t_allocs *old_allocated_pages) {
    t_arena *curr;

    curr = old_allocated_pages->arenas;
    while (curr != NULL) {
        write(1, "a", 1);
        add_arena_to_allocated_pages(curr->addr, curr->type, curr->size);
        curr = curr->next;
    }
}
