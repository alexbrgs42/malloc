# include "../include/malloc.h"

void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc) {
    ptr->size = size;
    ptr->prev = prev;
    ptr->next = next;
    ptr->is_malloc = is_malloc;
}

void mark_block(void *ptr, size_t size) {
    t_metadata *ptr_meta;
    t_metadata *next_meta;

    ptr_meta = (t_metadata *)ptr;
    next_meta = (t_metadata *)(ptr_meta->next);
    if (ptr_meta->size - size < sizeof(t_metadata))
        size = ptr_meta->size;

    if (ptr_meta->size == size) {
        set_metadata(ptr, size, ptr_meta->prev, ptr_meta->next, true);
        return ;
    }
    set_metadata(ptr + size, ptr_meta->size - size, ptr, ptr_meta->next, false);
    if (next_meta != NULL)
        set_metadata(next_meta, next_meta->size, ptr + size, next_meta->next, next_meta->is_malloc);
    set_metadata(ptr, size, ptr_meta->prev, ptr + size, true);

}
