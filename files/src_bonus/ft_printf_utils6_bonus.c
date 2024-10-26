/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils6_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:09:01 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/24 12:09:08 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

static void	handle_zero_flag(t_flags flags, int number, int *n_str, char *str)
{
	int	n_aux;

	if (number < 0)
		print_char('-');
	else if (number >= 0 && flags.plus)
	{
		print_char('+');
		(*n_str)++;
	}
	else if (flags.space)
	{
		print_char(' ');
		(*n_str)++;
	}
	n_aux = *n_str;
	while (flags.width-- > n_aux)
		(*n_str) += print_char('0');
	if (number < 0)
		print_string(str + 1);
	else
		print_string(str);
}

int	is_null_number(int number, t_flags flags)
{
	if (number == 0 && flags.dot && flags.precision == 0)
		return (1);
	return (0);
}

static int	handle_sign(int number, t_flags flags, int *n_str)
{
	if (number < 0)
	{
		print_char('-');
		return (-1);
	}
	else if (flags.plus)
	{
		print_char('+');
		(*n_str)++;
		return (1);
	}
	else if (flags.space)
	{
		print_char(' ');
		(*n_str)++;
		return (1);
	}
	return (0);
}

static void	handle_minus_flag(t_flags flags, int number, int *n_str, char *str)
{
	int	n_aux;
	int	is_null;

	is_null = is_null_number(number, flags);
	n_aux = *n_str + handle_sign(number, flags, n_str);
	if (flags.precision > n_aux)
	{
		while (flags.precision-- > n_aux)
			(*n_str) += print_char('0');
	}
	if (is_null)
	{
		if (flags.width > 0)
			print_char(' ');
	}
	else if (number < 0)
		print_string(str + 1);
	else
		print_string(str);
	n_aux = *n_str;
	while (flags.width-- > n_aux)
		(*n_str) += print_char(' ');
}

int	print_int_with_flags(va_list args, t_flags flags)
{
	char	*str;
	int		number;
	int		n_str;

	number = va_arg(args, int);
	str = ft_itoa(number);
	n_str = ft_strlen(str);
	if (flags.zero && flags.dot == 0 && flags.minus == 0)
		handle_zero_flag(flags, number, &n_str, str);
	else if (flags.minus)
		handle_minus_flag(flags, number, &n_str, str);
	else
		handle_other_flag(flags, number, &n_str, str);
	free(str);
	return (n_str);
}
