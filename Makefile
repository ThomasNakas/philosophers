# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/04 13:02:26 by tnakas            #+#    #+#              #
#    Updated: 2024/08/25 22:03:03 by tnakas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I.

SRC = src/init.c src/main.c src/parsing.c src/protect_one.c \
		src/protect_two.c src/routine_philos.c src/routine_philos_utils.c \
		src/routine_supervisor.c src/utils_one.c src/utils_two.c \

OBJ = $(SRC:.c=.o)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLUE)Linking $@...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)Executable $(NAME) created successfully!$(RESET)"


%.o: %.c
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(YELLOW)Cleaned up object files and temporary files.$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning all build files...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)Fully cleaned including executable and libraries.$(RESET)"

re: fclean all

.PHONY: all clean fclean re