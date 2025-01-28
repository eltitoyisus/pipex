# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jramos-a <jramos-a@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 09:37:18 by jramos-a          #+#    #+#              #
#    Updated: 2025/01/27 09:37:18 by jramos-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = cc
FLAGS = -Werror -Wall -Wextra -fsanitize=address
NAME = pipex
RM = rm -rf

SRC = main.c	\
		utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

libft/libft.a:
	@$(MAKE) -C libft

$(NAME): $(OBJ) libft/libft.a
	@$(CC) $(FLAGS) $(OBJ) libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean: 
	@$(RM) $(OBJ)
	@$(MAKE) clean -C libft

fclean: 
	@$(RM) $(OBJ) $(NAME)
	@$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re