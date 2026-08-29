##
## EPITECH PROJECT, 2017
## Makefile
## File description:
##
##

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	my_runner


all:	$(NAME)

$(NAME):	 $(OBJ)
	 gcc -o $(NAME) $(OBJ) -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -Wall -Wextra


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
