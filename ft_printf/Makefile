MY_SOURCES = ft_printf.c \
		ft_printf2.c

MY_OBJECTS = ${MY_SOURCES:.c=.o}

CFLAGS	= -Wall -Wextra -Werror

NAME	= libftprintf.a

CC	= gcc

RM	= rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${MY_OBJECTS}
	ar -rc ${NAME} ${MY_OBJECTS}
	ranlib ${NAME}

all:	${NAME}

clean:
	${RM} ${MY_OBJECTS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
