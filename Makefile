SRC_PATH	:=	src
OBJ_PATH	:=	obj

SRC_FILES	:=	global_variable.c malloc.c free.c realloc.c calloc.c best_fit.c display.c allocated_pages.c metadata.c new_arena.c

SRC	:=	$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ	:=	$(patsubst $(SRC_PATH)/%, $(OBJ_PATH)/%, $(SRC:.c=.o))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME			:=	libft_malloc_$(HOSTTYPE).so
SYM_LINK_NAME	:=	libft_malloc.so
CFLAGS			:=	-Wall -Wextra -g3
INCL			:=	-Iinclude
LIB				:=	-Llibft -lft -Lft_printf -lftprintf
LIBFT			:=	libft/libft.a
PRINTF			:=	ft_printf/libftprintf.a

#################################################################
#                                                               #
#                             BUILD                             #
#                                                               #
#################################################################

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	gcc -fPIC -shared $(CFLAGS) $(INCL) -c -o $@ $< $(LIB)

$(NAME):	$(LIBFT) $(PRINTF) $(OBJ_PATH) $(OBJ)
	gcc -fPIC -shared $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)
	ln -sf $(NAME) $(SYM_LINK_NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C ft_printf

#################################################################
#                                                               #
#                          USUAL RULES                          #
#                                                               #
#################################################################

all:	$(NAME)

clean:
	rm -rf $(OBJ_PATH)
	make clean -C libft
	make clean -C ft_printf

fclean:	clean
	rm -rf $(NAME) $(SYM_LINK_NAME)
	make fclean -C libft
	make fclean -C ft_printf

re: fclean all

.PHONY: all clean fclean re
