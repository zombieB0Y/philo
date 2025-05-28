CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
SRC = philo.c init_functions.c setup.c garbage_collector.c utils.c
OBJ = $(SRC:.c=.o)
NAME = philo

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -fsanitize=thread -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all