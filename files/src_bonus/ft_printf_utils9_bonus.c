/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils9_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:18:29 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/24 13:18:32 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

int	ft_numlen(unsigned int n, unsigned int base)
{
	if (n < base)
		return (1);
	else
	{
		return (1 + ft_numlen(n / base, base));
	}
}

void	print_hex_message(t_flags flags, unsigned int hex_number, int is_null)
{
	if (is_null)
	{
		if (flags.width > 0)
			print_char(' ');
	}
	else if (flags.type == 'x')
		print_hex(hex_number, HEX_LOWER);
	else
		print_hex(hex_number, HEX_UPPER);
}

static void	manage_padding1(t_flags flags, int n_aux, int *n_str)
{
	if (flags.dot)
	{
		if (flags.width > flags.precision + 2)
			while (flags.width-- > flags.precision + 2)
				*n_str += print_char(' ');
	}
	else
	{
		if (flags.width > n_aux + 2)
			while (flags.width-- > n_aux + 2)
				*n_str += print_char(' ');
	}
	print_char('0');
	print_char(flags.type);
	*n_str += 2;
}

static void	manage_padding2(t_flags flags, int n_aux, int *n_str)
{
	if (flags.dot && flags.precision > n_aux)
	{
		if (flags.width > flags.precision)
			while (flags.width-- > flags.precision)
				*n_str += print_char(' ');
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
}

void	handle_other_flag_hex(t_flags flags, unsigned int hex_number,
		int *n_str, int is_null)
{
	int	n_aux;

	n_aux = *n_str;
	if (flags.hashtag && hex_number != 0)
		manage_padding1(flags, n_aux, n_str);
	else
		manage_padding2(flags, n_aux, n_str);
	if (flags.precision > n_aux)
		while (flags.precision-- > n_aux)
			*n_str += print_char('0');
	print_hex_message(flags, hex_number, is_null);
}
