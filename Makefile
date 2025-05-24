CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC = philo.c
OBJ = $(SRC:.c=.o)
NAME = philo
all: $(NAME)
$(NAME): $(OBJ) philo.h
	$(CC) $(OBJ) -lpthread -o $(NAME)

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all