# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/04 15:08:31 by pbongiov          #+#    #+#              #
#    Updated: 2025/11/17 18:32:27 by pbongiov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CFLAGS = -g -Iinclude -Wall -Wextra -Werror

LDFLAGS = -lreadline

SRC := $(shell find src/ -name '*.c')

OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

r:
	make re && clear && ./$(NAME)

v:
	make re && clear &&  valgrind --suppressions=readline.supp ./$(NAME)

vl:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --suppressions=readline.supp ./$(NAME)

vc:
	make re && clear && valgrind --track-origins=yes --suppressions=readline.supp ./$(NAME)

vall:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./$(NAME)

.PHONY: all clean fclean re r
