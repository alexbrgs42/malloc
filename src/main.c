# include "../include/malloc.h"

t_allocs    alloc_table = { 0, 0, NULL };

int main() {
    ft_strlen("hello");
    printf("{ %d %d %p }\n", alloc_table.tiny_arena, alloc_table.small_arena, alloc_table.head);
    printf("%d\n", ALIGN(10));
}
