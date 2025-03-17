##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC	=	*.c

NAME	=	my_sudo

all:	$(NAME)

$(NAME):
	gcc -g3 -o $(NAME) $(SRC) -lcrypt

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

style:
	coding-style.sh . .
	clear
	cat coding-style-reports.log
	rm -rf coding-style-reports.log

test: fclean
	gcc -g3 -o $(NAME) $(SRC) -lcrypt
	sudo chown root:root my_sudo
	sudo chmod u+s my_sudo
