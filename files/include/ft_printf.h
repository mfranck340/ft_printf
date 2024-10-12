/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:30:06 by ffierro-          #+#    #+#             */
/*   Updated: 2024/10/11 10:30:09 by ffierro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include "../libft/libft.h"

int	ft_printf(char const *format, ...);
int	print_char(char c);
int	print_string(char *str);
int	print_int(int n);
int	print_unsigned(unsigned int n);
int	print_hex(unsigned long n, char *dict);
int	print_pointer(void *p);

#endif
