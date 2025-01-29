# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 22:32:48 by jramos-a          #+#    #+#              #
#    Updated: 2025/01/28 22:32:48 by jramos-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Werror -Wall -Wextra
NAME = pipex
RM = rm -rf

SRC = main.c	\
		utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

libft/libft.a:
	@$(MAKE) -C LIB

$(NAME): $(OBJ) LIB/libft.a
	@$(CC) $(FLAGS) $(OBJ) LIB/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	@$(RM) $(OBJ)
	@$(MAKE) clean -C LIB

fclean: 
	@$(RM) $(OBJ) $(NAME)
	@$(MAKE) fclean -C LIB

re: fclean all

.PHONY: all clean fclean re