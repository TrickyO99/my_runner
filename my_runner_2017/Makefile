##
## EPITECH PROJECT, 2017
## Makefile
## File description:
##
##

SRC	=	src/*.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_runner


all:	$(NAME)

$(NAME):	 $(OBJ)
	 gcc -o $(NAME) $(SRC) -l c_graph_prog -Wall -Wextra


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
