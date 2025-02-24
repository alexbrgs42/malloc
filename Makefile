SRC_PATH	:=	src
OBJ_PATH	:=	obj

SRC_FILES	:=	malloc.c free.c realloc.c calloc.c best_fit.c display.c allocated_pages.c metadata.c new_arena.c

SRC	:=	$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ	:=	$(patsubst $(SRC_PATH)/%, $(OBJ_PATH)/%, $(SRC:.c=.o))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SYM_LINK_NAME	:=	libft_malloc_$(HOSTTYPE).so
NAME			:=	libft_malloc.so
CFLAGS			:=	-Wall -Wextra -Werror -g3
INCL			:=	-Iinclude
LIB				:=	-Llibft -lft
LIBFT			:=	libft/libft.a

#################################################################
#                                                               #
#                             BUILD                             #
#                                                               #
#################################################################

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	gcc -fPIC -shared $(CFLAGS) $(INCL) -c -o $@ $< $(LIB)

$(NAME):	$(LIBFT) $(OBJ_PATH) $(OBJ)
	gcc -fPIC -shared $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)
	ln -sf $(NAME) $(SYM_LINK_NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(LIBFT):
	make -C libft

#################################################################
#                                                               #
#                          USUAL RULES                          #
#                                                               #
#################################################################

all:	$(NAME)

clean:
	rm -rf $(OBJ_PATH)
	make clean -C libft

fclean:	clean
	rm -rf $(NAME) $(SYM_LINK_NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
