SRC_PATH	:=	src
OBJ_PATH	:=	obj

SRC_FILES	:=	main.c allocation.c best_fit.c display.c

SRC	:=	$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ	:=	$(patsubst $(SRC_PATH)/%, $(OBJ_PATH)/%, $(SRC:.c=.o))

NAME	:=	executable
CFLAGS	:=	-Wall -Wextra -Werror -g3
INCL	:=	-Iinclude
LIB		:=	-Llibft -lft
LIBFT	:=	libft/libft.a

#################################################################
#                                                               #
#                             BUILD                             #
#                                                               #
#################################################################

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	gcc $(CFLAGS) $(INCL) -c -o $@ $< $(LIB)

$(NAME):	$(LIBFT) $(OBJ_PATH) $(OBJ)
	gcc $(CFLAGS) $(INCL) $(OBJ) -o $(NAME) $(LIB)

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
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
