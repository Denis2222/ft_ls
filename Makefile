.PHONY: libft

SRCS = main.c

NAME = ft_ls
GCC_FLAG = -Wall -Werror -Wextra
CC = gcc #$(GCC_FLAG)

OBJS = $(SRCS:.c=.o)

all: libft $(NAME)
	./ft_ls

libft:
	make -C ./libft/

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -Llibft -lft

clean:
	rm -f $(NAME)
	rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean

re: fclean all
