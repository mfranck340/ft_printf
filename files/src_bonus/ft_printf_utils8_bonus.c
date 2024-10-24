/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils8_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:18:18 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/24 13:18:21 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

void	handle_zero_flag_hex(t_flags flags, unsigned int hex_number,
		int *n_str, int is_null)
{
	int	n_aux;

	if (flags.hashtag && hex_number != 0)
	{
		print_char('0');
		print_char(flags.type);
		*n_str += 2;
	}
	n_aux = *n_str;
	while (flags.width > n_aux)
	{
		*n_str += print_char('0');
		flags.width--;
	}
	print_hex_message(flags, hex_number, is_null);
}

void	handle_minus_flag_hex(t_flags flags, unsigned int hex_number,
		int *n_str, int is_null)
{
	int	n_aux;

	n_aux = *n_str;
	if (flags.hashtag && hex_number != 0)
	{
		print_char('0');
		print_char(flags.type);
		*n_str += 2;
	}
	if (flags.precision > n_aux)
	{
		while (flags.precision-- > n_aux)
			*n_str += print_char('0');
	}
	print_hex_message(flags, hex_number, is_null);
	n_aux = *n_str;
	while (flags.width-- > n_aux)
		*n_str += print_char(' ');
}

int	print_hex_with_flags(va_list args, t_flags flags)
{
	unsigned int	hex_number;
	int				n_str;
	int				is_null;

	hex_number = va_arg(args, unsigned int);
	n_str = ft_numlen(hex_number, 16);
	is_null = 0;
	if (hex_number == 0 && flags.dot && flags.precision == 0)
		is_null = 1;
	if (flags.zero && flags.dot == 0 && flags.minus == 0)
		handle_zero_flag_hex(flags, hex_number, &n_str, is_null);
	else if (flags.minus)
		handle_minus_flag_hex(flags, hex_number, &n_str, is_null);
	else
		handle_other_flag_hex(flags, hex_number, &n_str, is_null);
	return (n_str);
}
