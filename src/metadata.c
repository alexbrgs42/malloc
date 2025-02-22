# include "../include/malloc.h"

void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc) {
    ptr->size = size;
    ptr->prev = prev;
    ptr->next = next;
    ptr->is_malloc = is_malloc;
}

void    mark_block(void *ptr, size_t size) {
    if (((t_metadata *)ptr)->size != size) {
        set_metadata(ptr + size, ((t_metadata *)ptr)->size - size, ptr, ((t_metadata *)ptr)->next, false);
    }
    if (((t_metadata *)ptr)->next != NULL)
        set_metadata(((t_metadata *)ptr)->next, ((t_metadata *)(((t_metadata *)ptr)->next))->size, ptr + size, ((t_metadata *)(((t_metadata *)ptr)->next))->next, ((t_metadata *)(((t_metadata *)ptr)->next))->is_malloc);
    set_metadata(ptr, size, ((t_metadata *)ptr)->prev, (((t_metadata *)ptr)->size != size ? ptr + size : ((t_metadata *)ptr)->next), true);
    ((t_metadata *)ptr)->size = ((t_metadata *)ptr)->size;
}
