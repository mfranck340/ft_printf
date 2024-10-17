/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:17:12 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/11 20:17:13 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_bonus.h"
#include <stdio.h>

int	get_flag_number(int *flag, char const *format, int index)
{
	int	n_flag;

	n_flag = 0;
	while (ft_isdigit(format[index + n_flag]))
	{
		if (*flag > (INT_MAX - (format[index + n_flag] - '0')) / 10)
			return (-1);
		*flag = *flag * 10 + format[index + n_flag] - '0';
		n_flag++;
	}
	return (n_flag);
}

int	turn_on_flags(const char *format, t_flags *flags, int n_aux)
{
	if (format[n_aux] == '-' && flags->width == 0)
		flags->minus = 1;
	else if (format[n_aux] == '0' && flags->width == 0)
		flags->zero = 1;
	else if (format[n_aux] == '+' && flags->width == 0)
		flags->plus = 1;
	else if (format[n_aux] == ' ' && flags->width == 0)
		flags->space = 1;
	else if (format[n_aux] == '#' && flags->width == 0)
		flags->hashtag = 1;
	else if (ft_strchr(CONVERSIONS, format[n_aux]))
	{
		flags->type = format[n_aux];
		return (1);
	}
	else
		return (-2);
	return (0);
}

int	handle_binary_flags(const char *format, t_flags *flags, int *n_flags)
{
	int	n_aux;

	n_aux = turn_on_flags(format, flags, *n_flags);
	if (n_aux == -2 || n_aux == 1)
		return (n_aux);
    (*n_flags)++;
    return (0);
}

int handle_width_precision(const char *format, t_flags *flags, int *n_flags)
{
    int n_aux;

    if (format[*n_flags] != '0' && ft_isdigit(format[*n_flags]) && flags->width == 0)
    {
        n_aux = get_flag_number(&flags->width, format, *n_flags);
        if (n_aux == -1)
            return (-1);
        *n_flags += n_aux;
    }
    else if (format[*n_flags] == '.' && flags->dot == 0)
    {
        flags->dot = 1;
        if (ft_isdigit(format[*n_flags + 1]))
        {
            n_aux = get_flag_number(&flags->precision, format, ++(*n_flags));
            if (n_aux == -1)
                return (-1);
            *n_flags += n_aux;
        }
        else
            (*n_flags)++;
    }
    return (0);
}

int get_flags(t_flags *flags, char const *format)
{
	int	n_flags;
	int	n_aux;

	n_flags = 0;
	ft_memset(flags, 0, sizeof(t_flags));
	while (format[n_flags])
	{
		n_aux = handle_width_precision(format, flags, &n_flags);
		if (n_aux == -1)
			return (-1);
		if (format[n_flags] != '.')
		{
			n_aux = handle_binary_flags(format, flags, &n_flags);
			if (n_aux == -2)
				return (-2);
			if (n_aux == 1)
				break ;
		}
	}
	return (n_flags);
}


