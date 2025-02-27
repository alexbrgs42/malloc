# include "../include/malloc.h"

void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc) {
    ptr->size = size;
    ptr->prev = prev;
    ptr->next = next;
    ptr->is_malloc = is_malloc;
}

void mark_block(void *ptr, size_t block_size, size_t size) {
    t_metadata *ptr_meta;
    t_metadata *next_meta;

    ptr_meta = (t_metadata *)ptr;
    next_meta = (t_metadata *)(ptr_meta->next);
    if (get_block_size(ptr_meta) - block_size < sizeof(t_metadata)) {
        block_size = get_block_size(ptr_meta);
    }
    if (get_block_size(ptr_meta) == block_size) {
        set_metadata(ptr, size, ptr_meta->prev, ptr_meta->next, true);
        return ;
    }
    set_metadata(ptr + block_size, get_block_size(ptr_meta) - block_size, ptr, ptr_meta->next, false);
    if (next_meta != NULL)
        set_metadata(next_meta, next_meta->size, ptr + block_size, next_meta->next, next_meta->is_malloc);
    set_metadata(ptr, size, ptr_meta->prev, ptr + block_size, true);
}
