
#include "ft_printf.h"

int	print_message(char const *format, va_list args)
{
	int		n_ret;

	n_ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			n_ret += print_format(&format, args);
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

	va_start(args, format);
	n_ret = print_message(format, args);
	va_end(args);
	return (n_ret);
}