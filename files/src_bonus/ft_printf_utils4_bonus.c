/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils4_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:21:10 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/24 12:21:33 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"

int	ft_numpointer(void *p)
{
	unsigned long	n;
	int				n_aux;

	if (!p)
		return (5);
	n = (unsigned long)p;
	n_aux = 0;
	while (n)
	{
		n = n / 16;
		n_aux++;
	}
	return (n_aux);
}

void	handle_zero_flag_p(t_flags flags, void *pointer, int *n_str)
{
	int	n_aux;

	n_aux = *n_str;
	if (!pointer)
	{
		while (flags.width-- > n_aux)
			*n_str += print_char(' ');
		ft_putstr_fd("(nil)", 1);
	}
	else
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd('x', 1);
		*n_str += 2;
		while (flags.width-- > n_aux)
			*n_str += print_char('0');
		print_hex((unsigned long) pointer, HEX_LOWER);
	}
}

void	handle_minus_flag_p(t_flags flags, void *pointer, int *n_str)
{
	int	n_aux;

	n_aux = *n_str;
	if (!pointer)
	{
		ft_putstr_fd("(nil)", 1);
		while (flags.width-- > 5)
			*n_str += print_char(' ');
	}
	else
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd('x', 1);
		*n_str += 2;
		if (flags.precision > n_aux)
		{
			while (flags.precision-- > n_aux)
				*n_str += print_char('0');
		}
		n_aux = *n_str;
		print_hex((unsigned long) pointer, HEX_LOWER);
		while (flags.width-- > n_aux)
			*n_str += print_char(' ');
	}
}

void	manage_padding_p(t_flags flags, int *n_str)
{
	int	n_aux;

	n_aux = *n_str;
	if (flags.dot && flags.precision > n_aux)
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
	*n_str += print_string("0x");
	if (flags.precision > n_aux)
	{
		while (flags.precision-- > n_aux)
			*n_str += print_char('0');
	}
}

int	print_pointer_with_flags(va_list args, t_flags flags)
{
	void	*pointer;
	int		n_str;

	pointer = va_arg(args, void *);
	n_str = ft_numpointer(pointer);
	if (flags.zero && flags.dot == 0 && flags.minus == 0)
		handle_zero_flag_p(flags, pointer, &n_str);
	else if (flags.minus)
		handle_minus_flag_p(flags, pointer, &n_str);
	else
	{
		if (!pointer)
		{
			while (flags.width-- > 5)
				n_str += print_char(' ');
			ft_putstr_fd("(nil)", 1);
		}
		else
		{
			manage_padding_p(flags, &n_str);
			print_hex((unsigned long) pointer, HEX_LOWER);
		}
	}
	return (n_str);
}
