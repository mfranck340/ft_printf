NAME = libftprintf.a
CC = cc
LIB = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
HEADER = include/ft_printf.h
HEADER_BONUS = include/ft_printf_bonus.h
SRCS = src/ft_printf.c src/ft_printf_utils.c src/ft_printf_utils2.c
OBJS = $(SRCS:.c=.o)
SRCS_BONUS = src_bonus/ft_printf_bonus.c src_bonus/ft_printf_utils_bonus.c \
				src_bonus/ft_printf_utils2_bonus.c \
				src_bonus/ft_printf_utils3_bonus.c \
				src_bonus/ft_printf_utils4_bonus.c \
				src_bonus/ft_printf_utils5_bonus.c \
				src_bonus/ft_printf_utils6_bonus.c \
				src_bonus/ft_printf_utils7_bonus.c \
				src_bonus/ft_printf_utils8_bonus.c \
				src_bonus/ft_printf_utils9_bonus.c \
				src_bonus/ft_printf_utils10_bonus.c 
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

# Dependencias de $(NAME)
$(NAME): libft $(OBJS)
	$(LIB) $(NAME) $(OBJS)

bonus: libft $(OBJS_BONUS)
	$(LIB) $(NAME) $(OBJS_BONUS)

libft:
	$(MAKE) -C libft
	cp libft/libft.a $(NAME)

# Regla para compilar los archivos de bonus
src_bonus/%.o: src_bonus/%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar los archivos principales
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
