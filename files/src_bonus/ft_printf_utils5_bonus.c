
#include "../include/ft_printf_bonus.h"

int	print_n_string(char *str, unsigned int n)
{
	int		n_ret;

	n_ret = 0;
	while (str && n--)
	{
		ft_putchar_fd(*str, 1);
		str++;
		n_ret++;
	}
	return (n_ret);
}

int	print_char_with_flags(va_list args, t_flags flags)
{
	int	n_str;

    n_str = 1;
	if (flags.minus)
	{
		n_str += print_char(va_arg(args, int));
		while (flags.width-- > 1)
			n_str += print_char(' ');
	}
	else
	{
		while (flags.width-- > 1)
			n_str += print_char(' ');
		n_str += print_char(va_arg(args, int));
	}
	return n_str;
}

int handle_null(t_flags flags)
{
	int	n_str;

	n_str = 6;
	if (flags.minus)
	{
		print_n_string("(null)", 6);
		while (flags.width-- > 6)
			n_str += print_char(' ');
	}
	else
	{
		while (flags.width-- > 6)
			n_str += print_char(' ');
		print_n_string("(null)", 6);
	}
	return n_str;
}

int handle_non_null(char *str, t_flags flags, int n_aux)
{
	int	n_str;

	n_str = n_aux;
	if (flags.minus)
	{
		print_n_string(str, n_aux);
		while (flags.width-- > n_aux)
			n_str += print_char(' ');
	}
	else
	{
		while (flags.width-- > n_aux)
			n_str += print_char(' ');
		print_n_string(str, n_aux);
	}
	return n_str;
}

int	print_string_with_flags(va_list args, t_flags flags)
{
	char	*str;
	int		n_aux, n_str;

	str = va_arg(args, char *);
	n_str = ft_strlen(str);
	if (flags.dot && flags.precision < n_str)
		n_str = flags.precision;
	n_aux = n_str;
	if (!str && (flags.dot == 0 || flags.precision >= 6))
		return handle_null(flags);
	return handle_non_null(str, flags, n_aux);
}
