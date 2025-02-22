# include "../include/malloc.h"

void    defragment(void *first_block, void *second_block) {
    t_metadata  *first_meta = (t_metadata *)first_block;
    t_metadata  *second_meta = (t_metadata *)second_block;

    set_metadata(first_block, first_meta->size + second_meta->size, first_meta->prev, second_meta->next, false);
    if (second_meta->next != NULL)
        set_metadata(second_meta->next, ((t_metadata *)second_meta->next)->size, first_block, ((t_metadata *)second_meta->next)->next, true);
    ft_bzero(second_block, sizeof(t_metadata));
}

bool    is_block_free(void *block) {
    return (block != NULL && ((t_metadata *)block)->is_malloc == false);
}
