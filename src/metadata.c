# include "../include/malloc.h"

void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc) {
    ptr->size = size;
    ptr->prev = prev;
    ptr->next = next;
    ptr->is_malloc = is_malloc;
}

void    mark_block(void *ptr, size_t size) {
    t_metadata  *ptr_meta = (t_metadata *)ptr;
    t_metadata  *next_meta = (t_metadata *)(ptr_meta->next);

    ft_printf("\n\n");
    // show_alloc_mem();
    ft_printf("\n\n");
    if (ptr_meta->size - size < sizeof(t_metadata) || ptr_meta->size == size) {
        set_metadata(ptr, size, ptr_meta->prev, ptr_meta->next, true);
        return ;
    }
    set_metadata(ptr + size, ptr_meta->size - size, ptr, ptr_meta->next, false);
    if (next_meta != NULL) {
        ft_printf("%p\n", ptr_meta->next);
        ft_printf("%d\n", (int)next_meta->size);
        ft_printf("%p\n", ptr + size);
        ft_printf("%p\n", next_meta->next);
        ft_printf("%s\n", (next_meta->is_malloc ? "true" : "false"));
        set_metadata(next_meta, next_meta->size, ptr + size, next_meta->next, next_meta->is_malloc);
    }
    set_metadata(ptr, size, ptr_meta->prev, ptr + size, true);
}

// 0x7f9dfff933c8 malloc et calloc 0x7f9df86fc020
// 0x7f9e006d7820