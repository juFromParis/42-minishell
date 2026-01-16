# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jderachi <jderachi@student.42.fr>          +#+  +:+ +:+         +#+     #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/15 12:20:00 by jderachi          #+#    #+#              #
#    Updated: 2025/12/12 17:45:00 by jderachi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell


# Compiler and flags
CC     = cc
CFLAGS = -Wall -Wextra -Werror -g

# Colors & Blink
GREEN  = \033[32m
RED    = \033[31m
YELLOW = \033[33m
CYAN   = \033[36m
RESET  = \033[0m
BLINK = \033[5m
NOBLINK = \033[25m


RM = rm -f

# Detect OS
UNAME_S := $(shell uname -s)

# Readline (auto-select per OS)
ifeq ($(UNAME_S),Darwin)
	READLINE_INC = -I$(shell brew --prefix readline)/include
	READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline
else ifeq ($(UNAME_S),Linux)
	READLINE_INC =
	READLINE_LIB = -lreadline
endif

# ======================= LIBFT ======================= #

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)/includes
LIBFT_LIB = -L$(LIBFT_DIR) -lft

# Includes
INCLUDES = -I./inc $(LIBFT_INC) $(READLINE_INC)

# Sources
SRCS = \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
	src/env/env1.c src/env/env2.c src/env/env3.c src/exec/exec_ast1.c src/exec/exec_ast2.c \
	src/exec/exec_command.c src/exec/exec_pipe.c src/exec/exec_redir.c src/exec/exec_redir_out.c src/exec/exec_redir_in.c\
	src/exec/exec_redir_append.c src/exec/exec_redir_heredocument1.c src/exec/exec_redir_heredocument2.c \
	src/exec/exec_permissions.c \
	src/builtins/builtin_cd.c src/builtins/builtin_pwd.c src/builtins/builtin_echo.c src/builtins/builtin_export.c src/builtins/builtin_unset.c src/builtins/builtin_env.c src/builtins/exec_builtins1.c \
	src/builtins/builtin_exit.c src/builtins/resolve_path.c \
	src/utils/utils1.c src/utils/utils2.c src/utils/utils3.c src/utils/utils4.c \
	src/expansion/wildcard1.c src/expansion/wildcard2.c src/expansion/wildcard3.c src/expansion/wildcard4.c \
	src/expansion/variable.c src/expansion/ast_expansion.c\
	src/main.c \
	src/parsing/ischeck.c \
	src/parsing/lexer.c \
	src/parsing/token.c \
	src/parsing/parsing.c \
	src/parsing/parsing_cmd.c \
	src/parsing/parsing_redir.c \
	src/parsing/parsing_arg.c \
	src/parsing/parsing_quotes.c \
	src/parsing/node.c \
	src/parsing/heredocs.c src/parsing/redirs.c \
	src/syntax_error/syntax_error.c \
	src/syntax_error/syntax_ope.c \
	src/syntax_error/syntax_cmd.c \
	src/syntax_error/syntax_redir.c \
	src/syntax_error/syntax_sub.c \
	src/heredoc_init/heredoc_init.c \
	src/heredoc_init/heredoc_utils.c \
	src/signals/listeners.c \
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
all: $(LIBFT) $(NAME)

# Compile libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

# Compile minishell
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(READLINE_LIB) -o $(NAME)
	@echo "$(CYAN)✓ $(NAME) compiled successfully!$(RESET)"
	@echo "$(CYAN)  __  __ _       _   _____ _          _ _ "
	@echo "$(CYAN) |..\/..(.)     (.) / ____|.|        |.| |"
	@echo "$(CYAN) |.\../.|_ _ __  _ | (___ |.|__   ___|.| |"
	@echo "$(CYAN) |.|\/|.|.| '_ \|.| \___ \|.'. \ / _ \.| |"
	@echo "$(CYAN) |.|  |.|.| | | |.|_____) |.| |.|  __/.| |"
	@echo "$(CYAN) |.|  |.|.|_| |_|._______/|.| |.|\___|.|_|"
	@echo "$(RESET)"
	@echo "$(BLINK)$(GREEN)✓ $(NAME) ready to start..$(RESET)"

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
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(YELLOW)✓ Object files removed!$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(YELLOW)✓ $(NAME) cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re valgrind