.PHONY: libft

SRCS = main.c \
	 opts.c \
	 error.c \
	 args.c \
	 ents.c \
	 ls.c \
	 print.c \
	 tools.c \
	 sorts.c \
	 sortsfct.c \
	 dir.c

NAME = ft_ls
GCC_FLAG = -Wall -Werror -Wextra -g
CC = gcc $(GCC_FLAG)

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
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
