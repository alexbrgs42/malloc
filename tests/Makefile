INC		:=	-I../include
LIBS	:=	-L../libft -lft -lft_malloc -L../
FLAGS	:=	-Wall -Werror -Wextra

all:
	gcc main1.c $(INC) $(LIBS) $(FLAGS) -o test1
	gcc main2.c $(INC) $(LIBS) $(FLAGS) -o test2
	gcc main3.c $(INC) $(LIBS) $(FLAGS) -o test3
	gcc main4.c $(INC) $(LIBS) $(FLAGS) -o test4
	gcc main5.c $(INC) $(LIBS) $(FLAGS) -o test5

clean:
	rm -rf test1 test2 test3 test4 test5

fclean:	clean

re:	fclean all

.PHONY: all clean fclean re
