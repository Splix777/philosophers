NAME = philoo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

SRC = philo/main.c \
	  philo/errors_and_exits.c \
	  philo/set_table.c \
	  philo/start_sim.c \
	  philo/utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re