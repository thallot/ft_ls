# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thallot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 14:51:59 by thallot           #+#    #+#              #
#    Updated: 2019/07/22 10:46:00 by thallot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

############## COLORS ##################
_WHITE=$ \x1b[37m
_BLUE=$ \x1b[36m
_GREEN=$ \033[1;32m
_GREY=$ \x1b[33m
_RED=$ \x1b[31m

############## FLAGS ##################

NAME = fdf
LIBFT= libft/libft.a
CC = gcc
MLX_FLAG = -lmlx -framework OpenGL -framework AppKit
FLAG = -Werror -Wall -Wextra

############## FILES ##################

SRC = src/main.c \
			src/parser.c \
			src/free.c \
			src/draw.c \
			src/mlx.c \

############## PATH ##################

OBJECTS	= $(SRC:.c=.o)

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJECTS) includes/fdf.h lib
	@$(CC) $(FLAG) $(MLX_FLAG) $(LIBFT) $(OBJECTS) -o $(NAME)
	@echo "$(_GREEN)[OK] $(_BLUE)Creation de $(_WHITE)fdf"

%.o: src/%.c  includes/fdf.h
	@$(CC) $(FLAG) -I $(HEADER) -o $@ -c

lib:
	@make -C libft

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -rf $(NAME) $(EXE)
	@make fclean -C libft
	@echo "$(_GREEN)[OK] $(_RED)Suprression de $(_WHITE)$(NAME)"

re: fclean all
