# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/04 15:08:31 by pbongiov          #+#    #+#              #
#    Updated: 2025/11/21 15:59:55 by pbongiov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CFLAGS = -Iinclude -Wall -Wextra -Werror

LDFLAGS = -lreadline

SRC := 	src/built-in/ft_cd2.c \
		src/built-in/ft_cd.c \
		src/built-in/ft_echo.c \
		src/built-in/ft_env.c \
		src/built-in/ft_exit.c \
		src/built-in/ft_export2.c \
		src/built-in/ft_export.c \
		src/built-in/ft_pwd.c \
		src/built-in/ft_unset.c \
		src/exec/error_handling.c \
		src/exec/execute_children.c \
		src/exec/exec_utils.c \
		src/exec/path_and_here_doc.c \
		src/parse/expansion_parse.c \
		src/parse/expansion_utils2.c \
		src/parse/expansion_utils.c \
		src/parse/list_manage.c \
		src/parse/parse_main.c \
		src/parse/redir_parse.c \
		src/parse/signals.c \
		src/parse/sintax_parse.c \
		src/parse/utils_parse.c \
		src/utils/libft/ft_itoa.c \
		src/utils/libft/ft_split.c \
		src/utils/libft/list_utils.c \
		src/utils/libft/utils_str2.c \
		src/utils/libft/utils_str3.c \
		src/utils/libft/utils_str.c \
		src/utils/map/functions.c \
		src/utils/map/utils2.c \
		src/utils/map/utils.c \
		src/utils/mini_utils/get_next_line.c \
		src/utils/mini_utils/many_lines.c \
		src/utils/mini_utils/utils1.c \
		src/utils/mini_utils/utils2.c \
		src/utils/mini_utils/utils.c \
		src/minishell.c

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
	make re && clear && ./minishell
v:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./minishell

.PHONY: all clean fclean re r
