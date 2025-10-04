# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/04 15:08:31 by pbongiov          #+#    #+#              #
#    Updated: 2025/10/04 19:16:16 by pbongiov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CFLAGS = -Iinclude #-Wall -Wextra -Werror

LDFLAGS = -lreadline

SRC := $(shell find src/ MAP/ -name '*.c')

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

.PHONY: all clean fclean re r
