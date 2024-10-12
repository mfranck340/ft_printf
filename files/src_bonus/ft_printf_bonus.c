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
#include <stdio.h>

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

int	print_n_string(char *str, int n)
{
	int		n_ret;

	n_ret = 0;
	if (!str && n >= 6)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (str && n--)
	{
		ft_putchar_fd(*str, 1);
		str++;
		n_ret++;
	}
	return (n_ret);
}

int	print_format_flags(va_list args, t_flags flags)
{
	char *str;
	int n_aux;
	int	number;

	int	n_str;

	n_str = 0;
	if (flags.type == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	else if (flags.type == 'c')
	{
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
	}
	else if (flags.type == 's')
	{
		str = va_arg(args, char *);
		n_str = ft_strlen(str);
		if (flags.dot && flags.precision < n_str)
			n_str = flags.precision;
		n_aux = n_str;
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
	}
	else if (flags.type == 'd' || flags.type == 'i')
	{
		number = va_arg(args, int);
		str = ft_itoa(number);
		n_str = ft_strlen(str);
		n_aux = n_str;
		if (flags.zero && flags.dot == 0 && flags.minus == 0)
		{
			if (number < 0)
				print_char('-');
			else if (number >= 0 && flags.plus)
			{
				print_char('+');
				n_str++;
				n_aux++;
			}
			else if (flags.space)
			{
				print_char(' ');
				n_str++;
				n_aux++;
			}
			while (flags.width-- > n_aux)
				n_str += print_char('0');
			if (number < 0)
				print_string(str + 1);
			else
				print_string(str);
		}
		else if (flags.minus)
		{
			if (number < 0)
				print_char('-');
			else if (number >= 0 && flags.plus)
			{
				print_char('+');
				n_str++;
				n_aux++;
			}
			else if (flags.space)
			{
				print_char(' ');
				n_str++;
				n_aux++;
			}
			if (flags.precision > n_aux)
			{
				while (flags.precision-- > n_aux)
					n_str += print_char('0');
			}
			if (number < 0)
				print_string(str + 1);
			else
				print_string(str);
			n_aux = n_str;
			while (flags.width-- > n_aux)
				n_str += print_char(' ');
		}
		else
		{
			if (number < 0 || flags.plus || flags.space)
			{
				if (flags.width > flags.precision + 1)
					while (flags.width-- > flags.precision + 1)
						n_str += print_char(' ');
			}
			else
				if (flags.width > flags.precision)
					while (flags.width-- > flags.precision)
						n_str += print_char(' ');
			if (number < 0)
			{
				print_char('-');
				if (flags.precision > n_aux - 1)
					while (flags.precision-- > n_aux - 1)
						n_str += print_char('0');
			}
			else
			{
				if (flags.plus)
				{
					print_char('+');
					n_str++;
				}
				else if (flags.space)
				{
					print_char(' ');
					n_str++;
				}
				if (flags.precision > n_aux)
					while (flags.precision-- > n_aux)
						n_str += print_char('0');
			}
			if (number < 0)
				print_string(str + 1);
			else
				print_string(str);
		}
		free(str);
	}

	return (n_str);
}

int get_flags(t_flags *flags, char const *format)
{
	int	n_flags;

	n_flags = 0;
	ft_memset(flags, 0, sizeof(t_flags));
	while (format[n_flags])
	{
		//printf("I: %c\n", format[n_flags]);
		if (format[n_flags] != '0' && ft_isdigit(format[n_flags]) && flags->width == 0)
		{
			while (ft_isdigit(format[n_flags]))
			{
				if (flags->width > (INT_MAX - (format[n_flags] - '0')) / 10)
					return (-1);
				flags->width = flags->width * 10 + format[n_flags] - '0';
				n_flags++;
			}
		}
		else if (format[n_flags] == '.' && flags->dot == 0)
		{
			flags->dot = 1;
			if (ft_isdigit(format[n_flags + 1]))
			{
				while (ft_isdigit(format[++n_flags]))
				{
					if (flags->precision > (INT_MAX - (format[n_flags] - '0')) / 10)
						return (-1);
					flags->precision = flags->precision * 10 + format[n_flags] - '0';
				}
			}
			else
				n_flags++;
		}
		else
		{
			if (format[n_flags] == '-' && flags->width == 0)
				flags->minus = 1;
			else if (format[n_flags] == '0' && flags->width == 0)
				flags->zero = 1;
			else if (format[n_flags] == '+' && flags->width == 0)
				flags->plus = 1;
			else if (format[n_flags] == ' ' && flags->width == 0)
				flags->space = 1;
			else if (format[n_flags] == '#' && flags->width == 0)
				flags->hashtag = 1;
			else if (ft_strchr(CONVERSIONS, format[n_flags]))
			{
				flags->type = format[n_flags];
				break ;
			}
			else
				return (-2);
			n_flags++;
		}
	}
	return (n_flags);
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
			if (ft_strchr(FLAGS, *(format + 1)) || ft_isdigit(*(format + 1)))
			{
				n_aux = get_flags(&flags, ++format);
				//printf(" || FLAGS: %d - %d - %d - %d || \n", flags.width, flags.minus, flags.zero, flags.precision);
				//printf(" || FLAGS: %d - %d - %d - %d || \n", flags.hashtag, flags.space, flags.plus, flags.type);
				//printf(" || FLAGS: %d || \n", flags.dot);
				//printf("N_AUX: %d\n", n_aux);
				if (n_aux == -1)
					return (-1);
				if (n_aux == -2)
				{
					ft_putchar_fd('%', 1);
					ft_putchar_fd(*format, 1);
					n_aux = 2;
				}
				else
				{
					format += n_aux;
					n_aux = print_format_flags(args, flags);
					if (n_aux == -1)
						return (-1);
				}
				n_ret += n_aux;
			}
			else
			{
				n_aux = print_format(++format, args);
				if (n_aux == -1)
					return (-1);
				n_ret += n_aux;
			}
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
