# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/15 12:20:00 by jderachi          #+#    #+#              #
#    Updated: 2025/12/05 11:47:53 by jderachi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Compiler and flags
CC     = cc
CFLAGS = -Wall -Wextra -Werror -g

# Colors
GREEN  = \033[32m
RED    = \033[31m
YELLOW = \033[33m
CYAN = \033[36m
RESET  = \033[0m

RM = rm -f

# Detect OS
UNAME_S := $(shell uname -s)

# Readline (auto-select per OS)
ifeq ($(UNAME_S),Darwin)
	READLINE_INC = -I$(shell brew --prefix readline)/include
	READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline
else ifeq ($(UNAME_S),Linux)
	READLINE_INC = -I/usr/include
	READLINE_LIB = -lreadline
endif

# Includes
INCLUDES = -I./inc $(READLINE_INC)

# Sources
SRCS = \
	src/main.c \
	src/parsing/utils.c \
	src/parsing/ischeck.c \
	src/parsing/lexer.c \
	src/parsing/token.c \
	src/parsing/parsing.c \
	src/parsing/cmd_split.c \
	src/parsing/node.c \
	src/syntax_error/syntax_error.c \
	src/syntax_error/syntax_ope.c \
	src/syntax_error/syntax_redir.c \
	src/syntax_error/syntax_sub.c \
	src/for_tests_to_delete/tests.c \
	src/exit.c

# Objects
OBJS = $(SRCS:.c=.o)

# Valgrind suppression file
SUPP = readline.supp

# Valgrind command
VAL = valgrind --leak-check=full --show-leak-kinds=all \
			   --track-origins=yes --suppressions=$(SUPP)

# Rules
all: $(NAME)

# Compile minishell
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(READLINE_LIB) -o $(NAME)
	@echo "$(CYAN)  __  __ _       _   _____ _          _ _ "
	@echo "$(CYAN) |  \/  (_)     (_) / ____| |        | | |"
	@echo "$(CYAN) | \  / |_ _ __  _ | (___ | |__   ___| | |"
	@echo "$(CYAN) | |\/| | | '_ \| | \___ \| '_ \ / _ \ | |"
	@echo "$(CYAN) | |  | | | | | | |_____) | | | |  __/ | |"
	@echo "$(CYAN) |_|  |_|_|_| |_|_|______/|_| |_|\___|_|_|"
	@echo "$(RESET)"
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"
	@echo "$(GREEN)✓ $(NAME) ready to start..$(RESET)"

# Compile each .c file into a .o file
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Valgrind rule
valgrind: $(NAME)
	@echo "$(YELLOW)→ Running Valgrind (with Readline suppressions)…$(RESET)"
	@$(VAL) ./$(NAME)

# Cleans
clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)✓ Object files removed! !$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)✓ $(NAME) cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re valgrind
