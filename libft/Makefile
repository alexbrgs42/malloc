IO_PATH		:=	src/IO
MEM_PATH	:=	src/memory
STR_PATH	:=	src/string
LIST_PATH	:=	src/linked_list
OBJ_PATH	:=	obj

MEM_SRC :=	$(MEM_PATH)/ft_memset.c \
			$(MEM_PATH)/ft_bzero.c \
			$(MEM_PATH)/ft_memcpy.c \
			$(MEM_PATH)/ft_memmove.c \
			$(MEM_PATH)/ft_memchr.c \
			$(MEM_PATH)/ft_memcmp.c
# 			$(MEM_PATH)/ft_calloc.c

STR_SRC	:=	$(STR_PATH)/ft_isalpha.c \
			$(STR_PATH)/ft_isdigit.c \
			$(STR_PATH)/ft_isalnum.c \
			$(STR_PATH)/ft_isascii.c \
			$(STR_PATH)/ft_isprint.c \
			$(STR_PATH)/ft_strlcpy.c \
			$(STR_PATH)/ft_strlcat.c \
			$(STR_PATH)/ft_toupper.c \
			$(STR_PATH)/ft_tolower.c \
			$(STR_PATH)/ft_strchr.c \
			$(STR_PATH)/ft_strrchr.c \
			$(STR_PATH)/ft_strncmp.c \
			$(STR_PATH)/ft_strlen.c \
			$(STR_PATH)/ft_strnstr.c \
			$(STR_PATH)/ft_atoi.c \
			$(STR_PATH)/ft_strdup.c \
			$(STR_PATH)/ft_substr.c \
			$(STR_PATH)/ft_strjoin.c \
			$(STR_PATH)/ft_strtrim.c \
			$(STR_PATH)/ft_split.c \
			$(STR_PATH)/ft_itoa.c \
			$(STR_PATH)/ft_strmapi.c \
			$(STR_PATH)/ft_striteri.c

IO_SRC	:=	$(IO_PATH)/ft_putchar_fd.c \
			$(IO_PATH)/ft_putstr_fd.c \
			$(IO_PATH)/ft_putendl_fd.c \
			$(IO_PATH)/ft_putnbr_fd.c

SRC_BONUS	:=	$(LIST_PATH)/ft_lstnew_bonus.c \
				$(LIST_PATH)/ft_lstadd_front_bonus.c \
				$(LIST_PATH)/ft_lstsize_bonus.c \
				$(LIST_PATH)/ft_lstlast_bonus.c \
				$(LIST_PATH)/ft_lstadd_back_bonus.c \
				$(LIST_PATH)/ft_lstdelone_bonus.c \
				$(LIST_PATH)/ft_lstclear_bonus.c \
				$(LIST_PATH)/ft_lstiter_bonus.c \
				$(LIST_PATH)/ft_lstmap_bonus.c

OBJ			= ${patsubst $(STR_PATH)/%, $(OBJ_PATH)/%, ${STR_SRC:.c=.o}} ${patsubst $(MEM_PATH)/%, $(OBJ_PATH)/%, ${MEM_SRC:.c=.o}} ${patsubst $(IO_PATH)/%, $(OBJ_PATH)/%, ${IO_SRC:.c=.o}}
OBJ_BONUS	= ${patsubst $(LIST_PATH)/%, $(OBJ_PATH)/%, ${SRC_BONUS:.c=.o}}

CFLAGS	=	-Wall -Wextra -Werror
INCL	=	-Iinclude
NAME	=	libft.a

#################################################################
#                                                               #
#                             BUILD                             #
#                                                               #
#################################################################

$(OBJ_PATH)/%.o:	$(MEM_PATH)/%.c
	cc ${CFLAGS} $(INCL) -c $< -o $@

$(OBJ_PATH)/%.o:	$(STR_PATH)/%.c
	cc ${CFLAGS} $(INCL) -c $< -o $@

$(OBJ_PATH)/%.o:	$(IO_PATH)/%.c
	cc ${CFLAGS} $(INCL) -c $< -o $@

$(OBJ_PATH)/%.o:	$(LIST_PATH)/%.c
	cc ${CFLAGS} $(INCL) -c $< -o $@

${NAME}:	${OBJ_PATH} ${OBJ}
	ar -rc ${NAME} ${OBJ}
	ranlib ${NAME}

bonus:	${OBJ_PATH} ${OBJ_BONUS}
	ar -rc ${NAME} ${OBJ_BONUS}
	ranlib ${NAME}

${OBJ_PATH}:
	mkdir -p ${OBJ_PATH}

#################################################################
#                                                               #
#                          USUAL RULES                          #
#                                                               #
#################################################################

all:	${NAME}

clean:
	rm -rf ${OBJ_PATH}

fclean:	clean
	rm -rf ${NAME}

re:	fclean all

.PHONY:	bonus all clean fclean re
