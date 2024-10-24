/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:30:24 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/11 10:30:26 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

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
		return (print_hex(va_arg(args, unsigned int), HEX_LOWER));
	else if (*format == 'X')
		return (print_hex(va_arg(args, unsigned int), HEX_UPPER));
	else if (*format == 'p')
		return (print_pointer(va_arg(args, void *)));
	else if (*format == '%')
		return (print_char('%'));
	else
	{
		ft_putchar_fd('%', 1);
		ft_putchar_fd(*format, 1);
		return (2);
	}
}

int	print_format_flags(va_list args, t_flags flags)
{
	if (flags.type == '%')
		return (print_char('%'));
	else if (flags.type == 'c')
		return (print_char_with_flags(args, flags));
	else if (flags.type == 's')
		return (print_string_with_flags(args, flags));
	else if (flags.type == 'd' || flags.type == 'i')
		return (print_int_with_flags(args, flags));
	else if (flags.type == 'u')
		return (print_unsigned_with_flags(args, flags));
	else if (flags.type == 'x' || flags.type == 'X')
		return (print_hex_with_flags(args, flags));
	else
		return (print_pointer_with_flags(args, flags));
}

int	handle_format(char const **format, va_list args, t_flags *flags)
{
	int	n_aux;

	if (ft_strchr(FLAGS, *(*format + 1)) || ft_isdigit(*(*format + 1)))
	{
		n_aux = get_flags(flags, ++(*format));
		if (n_aux == -1)
			return (-1);
		if (n_aux == -2)
		{
			ft_putchar_fd('%', 1);
			ft_putchar_fd(**format, 1);
			return (2);
		}
		(*format) += n_aux;
		return (print_format_flags(args, *flags));
	}
	return (print_format(++(*format), args));
}

int	print_message(char const *format, va_list args)
{
	int		n_ret;
	int		n_aux;
	t_flags	flags;

	n_ret = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '\0')
		{
			n_aux = handle_format(&format, args, &flags);
			if (n_aux == -1)
				return (-1);
			n_ret += n_aux;
		}
		else
		{
			ft_putchar_fd(*format, 1);
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
