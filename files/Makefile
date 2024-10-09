NAME = libftprintf.a
CC = cc
LIB = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c
OBJS = $(SRCS:.c=.o)
HEADER = ft_printf.h

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	cp libft/libft.a $(NAME)
	$(LIB) $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re