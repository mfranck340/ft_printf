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
	int n_aux;

	if (!p)
		return (5);
	n = (unsigned long)p;
	n_aux = 0;
	while (n)
	{
		n = n / 16;
		n_aux++;
	}
	return(n_aux);
}



void	print_unsigned_message(t_flags flags, unsigned int hex_number, int is_null)
{
	if (is_null)
	{
		if (flags.width > 0)
			print_char(' ');
	}
	else
		print_unsigned(hex_number);
}

void	handle_minus_flag_unsigned(t_flags flags, unsigned int hex_number, int *n_str, int is_null)
{
	int n_aux;

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

void	handle_other_flag_unsigned(t_flags flags, unsigned int hex_number, int *n_str, int is_null)
{
	int n_aux;

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
			while (flags.width > n_aux)
			{
				*n_str += print_char(' ');
				flags.width--;
			}
	}
	print_unsigned_message(flags, hex_number, is_null);
}
	
int	print_unsigned_with_flags(va_list args, t_flags flags)
{
	unsigned int hex_number;
	int n_str;
	int is_null;
	int n_aux;

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


int	print_format_flags(va_list args, t_flags flags)
{
	int n_aux;
	void	*pointer;

	int	n_str;

	n_str = 0;
	if (flags.type == '%')
		n_str = print_char('%');
	else if (flags.type == 'c')
		n_str = print_char_with_flags(args, flags);
	else if (flags.type == 's')
		n_str = print_string_with_flags(args, flags);
	else if (flags.type == 'd' || flags.type == 'i')
		n_str = print_int_with_flags(args, flags);
	else if (flags.type == 'u')
		n_str = print_unsigned_with_flags(args, flags);
	else if (flags.type == 'x' || flags.type == 'X')
		n_str = print_hex_with_flags(args, flags);
	else
	{
		pointer = va_arg(args, void *);
		n_str = ft_numpointer(pointer);
		n_aux = n_str;
		if (flags.zero && flags.dot == 0 && flags.minus == 0)
		{
			if (!pointer)
			{
				while (flags.width-- > n_aux)
					n_str += print_char(' ');
				ft_putstr_fd("(nil)", 1);
			}
			else
			{
				ft_putchar_fd('0', 1);
				ft_putchar_fd('x', 1);
				n_str += 2;
				while (flags.width-- > n_aux)
					n_str += print_char('0');
				print_hex((unsigned long) pointer, HEX_LOWER);
			}
		}
		else if (flags.minus)
		{
			if (!pointer)
			{
				ft_putstr_fd("(nil)", 1);
				while (flags.width-- > 5)
					n_str += print_char(' ');
			}
			else
			{
				ft_putchar_fd('0', 1);
				ft_putchar_fd('x', 1);
				n_str += 2;
				if (flags.precision > n_aux)
				{
					while (flags.precision-- > n_aux)
						n_str += print_char('0');
				}
				n_aux = n_str;
				print_hex((unsigned long) pointer, HEX_LOWER);
				while (flags.width-- > n_aux)
					n_str += print_char(' ');
			}
		}
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
				if (flags.dot && flags.precision > n_aux)
				{
					if (flags.width > flags.precision + 2)
						while (flags.width-- > flags.precision + 2)
							n_str += print_char(' ');
				}
				else
				{
					if (flags.width > n_aux + 2)
						while (flags.width-- > n_aux + 2)
							n_str += print_char(' ');
				}
				ft_putchar_fd('0', 1);
				ft_putchar_fd('x', 1);
				n_str += 2;
				if (flags.precision > n_aux)
				{
					while (flags.precision-- > n_aux)
						n_str += print_char('0');
				}
				print_hex((unsigned long) pointer, HEX_LOWER);
			}
		}
	}
	return (n_str);
}
