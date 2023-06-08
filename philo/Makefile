NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

SRC = main.c \
	  actions.c \
	  errors_and_exits.c \
	  set_table.c \
	  simulation.c \
	  utils.c \

OBJ_DIR = OBJ

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
CHECKMARK = ✔
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(CHECKMARK) $(NAME) created.$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)$(CHECKMARK) $(NAME) cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(CHECKMARK) $(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

test: $(NAME)
	@./$(NAME) 4 410 200 200 10
	@./$(NAME) 4 310 150 150 10
	@./$(NAME) 4 410 200 200
	@./$(NAME) 4 310 150 150
	@echo "$(GREEN)$(CHECKMARK) $(NAME) test passed.$(RESET)"
	