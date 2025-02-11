SRC_PATH	:=	ressources
OBJ_PATH	:=	obj

SRC	:=	$(SRC_PATH)/align.c
OBJ	:=	$(patsubst $(SRC_PATH)/%, $(OBJ_PATH)/%, $(SRC:.c=.o))

NAME	:=	executable
CFLAGS	:=	-Wall -Wextra -Werror
INCL	:=	-Iinclude

#################################################################
#                                                               #
#                             BUILD                             #
#                                                               #
#################################################################

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	gcc $(CFLAGS) $(INCL) -c -o $@ $<

$(NAME):	$(OBJ_PATH) $(OBJ)
	gcc $(CFLAGS) $(INCL) $(OBJ) -o $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

#################################################################
#                                                               #
#                          USUAL RULES                          #
#                                                               #
#################################################################

all:	$(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
