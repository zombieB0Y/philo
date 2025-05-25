CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
SRC = philo.c init_functions.c setup.c garbage_collector.c
OBJ = $(SRC:.c=.o)
NAME = philo
all: $(NAME)
$(NAME): $(OBJ) philo.h
	$(CC) $(OBJ) -lpthread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all