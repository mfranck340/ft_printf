
#include "ft_printf.h"

int	print_char(char c)
{
	ft_putchar(c);
	return (1);
}

int	print_string(char *str)
{
	int		n_ret;

	n_ret = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (*str)
	{
		ft_putchar(*str);
		str++;
		n_ret++;
	}
	return (n_ret);
}

int	print_format(char const *format, va_list args)
{
	if (*format == 'c')
		return (print_char(va_arg(args, int)));
	else if (*format == 's')
		return (print_string(va_arg(args, char *)));
	else if (*format == 'd' || *format == 'i')
		return (print_int(va_arg(args, int)));
	else if (*format == 'u')
		return (print_unsigned(va_arg(args, unsigned int)));
	else if (*format == 'x')
		return (print_hex(va_arg(args, unsigned int), 0));
	else if (*format == 'X')
		return (print_hex(va_arg(args, unsigned int), 1));
	else if (*format == 'p')
		return (print_pointer(va_arg(args, void *)));
	else if (*format == '%')
		return (print_char('%'));
	else
	{
		ft_putchar('%');
		ft_putchar(*format);
		return (2);
	}
}

int	print_message(char const *format, va_list args)
{
	int		n_ret;

	n_ret = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '\0')
		{
			format++;
			n_ret += print_format(format, args);
		}
		else
		{
			ft_putchar(*format);
			n_ret++;
		}
		format++;
	}
	return (n_ret);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		n_ret;

	if (!format)
		return (-1);
	va_start(args, format);
	n_ret = print_message(format, args);
	va_end(args);
	return (n_ret);
}