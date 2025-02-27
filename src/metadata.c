# include "../include/malloc.h"

/// @brief Set the metadata at the given address `ptr` with the given parameters.
/// @param ptr 
/// @param size 
/// @param prev 
/// @param next 
/// @param is_malloc 
void    set_metadata(t_metadata *ptr, size_t size, void *prev, void *next, bool is_malloc) {
    ptr->size = size;
    ptr->prev = prev;
    ptr->next = next;
    ptr->is_malloc = is_malloc;
}

/// @brief Sets metadatas changing after a malloc call.
/// @param ptr 
/// @param block_size 
/// @param size 
void mark_block(void *ptr, size_t block_size, size_t size) {
    t_metadata *ptr_meta;
    t_metadata *next_meta;

    ptr_meta = (t_metadata *)ptr;
    next_meta = (t_metadata *)ptr_meta->next;
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

/// @brief The real size of an allocated block (requested size + metadata + alignment).
/// @param meta 
/// @return The size as a `size_t`.
size_t  get_block_size(t_metadata *meta) {
    t_arena *arena;

    if (meta->next == NULL) {
        arena = get_arena_of_block(meta);
        if (arena == NULL)
            return 0;
        return (size_t)(arena->addr + arena->size - (void *)meta);
    }
    return (size_t)(meta->next - (void *)meta);
}

/// @brief Searches for the arena that containes the given metadata.
/// @param meta 
/// @return The arena or NULL if it isn't in any arena.
t_arena *get_arena_of_block(void *meta) {
    t_arena    *arena;

    if (allocated_pages == NULL)
        return NULL;
    arena = allocated_pages->arenas;
    while (arena != NULL) {
        if (meta >= arena->addr && meta < arena->addr + arena->size)
            return arena;
        arena = arena->next;
    }
    return NULL;
}
