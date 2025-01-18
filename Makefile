
CC = gcc
CFLAGS = -Wall -Wextra -Werror
PRINTF = make /printf/makefile

name: pipex

SRC = pipex.c \
	  pipex_utils.c \
	  pipex_utils2.c \
	  pipex_utils3.c

OBJ = $(SRC:.c=.o)

all: $(name)

$(name): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(name)
	$(PRINTF)

clean: rm -f $(OBJ)

fclean: clean
	rm -f $(name)

re: fclean all

.PHONY: all clean fclean re
