NAME = minishell
CC = cc
CFLAGS = -Iinclude #-Wall -Werror -Wextra
SRC := $(shell find src/ -name '*.c')

SRCOBJ = obj/

OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(SRCOBJ),$(OBJ))


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

r:
	make re && ./$(NAME)

.PHONY: all clean fclean re