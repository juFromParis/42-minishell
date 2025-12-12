# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jderachi <jderachi@student.42.fr>          +#+  +:+ +:+         +#+     #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 10:49:50 by jderachi          #+#    #+#              #
#    Updated: 2025/12/12 18:00:00 by jderachi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = libft.a

# Compiler and flags
CC     = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

# Colors
GREEN  = \033[32m
YELLOW = \033[33m
CYAN   = \033[36m
RESET  = \033[0m

# Sources
SRC = \
	src/ft_atoi.c \
	src/ft_bzero.c \
	src/ft_calloc.c \
	src/ft_isspace.c \
	src/ft_isalnum.c \
	src/ft_isalpha.c \
	src/ft_isascii.c \
	src/ft_isdigit.c \
	src/ft_isprint.c \
	src/ft_itoa.c \
	src/ft_putchar_fd.c \
	src/ft_putendl_fd.c \
	src/ft_putnbr_fd.c \
	src/ft_putstr_fd.c \
	src/ft_strjoin.c \
	src/ft_memchr.c \
	src/ft_memcmp.c \
	src/ft_memcpy.c \
	src/ft_memmove.c \
	src/ft_memset.c \
	src/ft_split.c \
	src/ft_strchr.c \
	src/ft_striteri.c \
	src/ft_strrchr.c \
	src/ft_strlcat.c \
	src/ft_strdup.c \
	src/ft_strndup.c \
	src/ft_strlcpy.c \
	src/ft_strlen.c \
	src/ft_arrlen.c \
	src/ft_strmapi.c \
	src/ft_strncmp.c \
	src/ft_strcmp.c \
	src/ft_strncpy.c \
	src/ft_strnstr.c \
	src/ft_strtrim.c \
	src/ft_substr.c \
	src/ft_tolower.c \
	src/ft_toupper.c

# Bonus sources
BNS = \
	src/ft_lstnew.c \
	src/ft_lstadd_front.c \
	src/ft_lstsize.c \
	src/ft_lstlast.c \
	src/ft_lstadd_back.c \
	src/ft_lstdelone.c \
	src/ft_lstclear.c \
	src/ft_lstiter.c \
	src/ft_lstmap.c

# Objects
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BNS:.c=.o)

# Includes
INCLUDES = -I.

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(CYAN)✓ libft compiled successfully$(RESET)"

bonus: $(OBJ) $(BONUS_OBJ)
	@ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "$(CYAN)✓ libft bonus compiled successfully$(RESET)"

# Compile each .c file into a .o file
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleans
clean:
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@echo "$(YELLOW)✓ libft objects removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)✓ libft cleaned$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
