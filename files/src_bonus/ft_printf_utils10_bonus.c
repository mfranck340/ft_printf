/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils10_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:52:21 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/24 16:52:26 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

static void	print_unsigned_message(t_flags flags, unsigned int hex_number,
		int is_null)
{
	if (is_null)
	{
		if (flags.width > 0)
			print_char(' ');
	}
	else
		print_unsigned(hex_number);
}

static void	handle_minus_flag_unsigned(t_flags flags, unsigned int hex_number,
		int *n_str, int is_null)
{
	int	n_aux;

	n_aux = *n_str;
	if (flags.precision > n_aux)
	{
		while (flags.precision-- > n_aux)
			*n_str += print_char('0');
	}
	print_unsigned_message(flags, hex_number, is_null);
	n_aux = *n_str;
	while (flags.width-- > n_aux)
		*n_str += print_char(' ');
}

static void	handle_other_flag_unsigned(t_flags flags, unsigned int hex_number,
		int *n_str, int is_null)
{
	int	n_aux;

	n_aux = *n_str;
	if (flags.dot && flags.precision > n_aux)
	{
		if (flags.width > flags.precision)
			while (flags.width-- > flags.precision)
				*n_str += print_char(' ');
		if (flags.precision > n_aux)
			while (flags.precision-- > n_aux)
				*n_str += print_char('0');
	}
	else
	{
		if (flags.width > n_aux)
		{
			while (flags.width > n_aux)
			{
				*n_str += print_char(' ');
				flags.width--;
			}
		}
	}
	print_unsigned_message(flags, hex_number, is_null);
}

int	print_unsigned_with_flags(va_list args, t_flags flags)
{
	unsigned int	hex_number;
	int				n_str;
	int				is_null;
	int				n_aux;

	hex_number = va_arg(args, unsigned int);
	n_str = ft_numlen(hex_number, 10);
	n_aux = n_str;
	is_null = 0;
	if (hex_number == 0 && flags.dot && flags.precision == 0)
		is_null = 1;
	if (flags.zero && flags.dot == 0 && flags.minus == 0)
	{
		while (flags.width-- > n_aux)
			n_str += print_char('0');
		print_unsigned(hex_number);
	}
	else if (flags.minus)
		handle_minus_flag_unsigned(flags, hex_number, &n_str, is_null);
	else
		handle_other_flag_unsigned(flags, hex_number, &n_str, is_null);
	return (n_str);
}
