# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 11:10:27 by fsalazar          #+#    #+#              #
#    Updated: 2023/06/12 11:10:28 by fsalazar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=thread

RM = rm -f

SRC = main.c \
	  actions.c \
	  actions2.c \
	  errors_and_exits.c \
	  set_table.c \
	  simulation.c \
	  utils.c \

OBJ_DIR = OBJ

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m
CHECKMARK = ✔

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(CHECKMARK) $(NAME) created.$(RESET)"
	@echo "$(GREEN)./$(NAME) <N_PHILS> <TIME_TO_DIE> <TIME_TO_EAT> <TIME_TO_SLEEP> [N_EAT]$(RESET)"

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
	@./$(NAME) 1 410 200 200 10
	@./$(NAME) 3 310 200 100 10
	@./$(NAME) 3 310 100 200 10
	@./$(NAME) 4 410 200 200 10
	@./$(NAME) 4 310 150 150 200
	@echo "$(GREEN)$(CHECKMARK) $(NAME) test passed.$(RESET)"
	
