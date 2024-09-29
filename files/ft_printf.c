
#include "ft_printf.h"

int	print_message(char const *format, va_list args)
{
	int		ret;

	ret = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;

		}
		else
		{
			ft_putchar(*format);
			ret++;
		}
		format++;
	}
	return (ret);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = print_message(format, args);
	va_end(args);
	return (ret);
}