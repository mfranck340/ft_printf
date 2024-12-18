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

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include "../libft/libft.h"

# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define CONVERSIONS "cspdiuxX%"
# define FLAGS "-0.# +"

typedef struct s_flags
{
	int		width;
	int		minus;
	int		zero;
	int		dot;
	int		precision;
	int		hashtag;
	int		space;
	int		plus;
	char	type;
}	t_flags;

int		ft_printf(char const *format, ...);
int		print_char(char c);
int		print_string(char *str);
int		print_int(int n);
int		print_unsigned(unsigned int n);
int		print_hex(unsigned long n, char *dict);
int		print_pointer(void *p);
int		get_flags(t_flags *flags, char const *format);
int		print_char_with_flags(va_list args, t_flags flags);
int		print_string_with_flags(va_list args, t_flags flags);
int		print_int_with_flags(va_list args, t_flags flags);
void	handle_other_flag(t_flags flags, int number, int *n_str, char *str);
int		is_null_number(int number, t_flags flags);
int		ft_numlen(unsigned int n, unsigned int base);
void	print_hex_message(t_flags flags, unsigned int hex_number, int is_null);
void	handle_other_flag_hex(t_flags flags, unsigned int hex_number,
			int *n_str, int is_null);
int		print_hex_with_flags(va_list args, t_flags flags);
int		print_unsigned_with_flags(va_list args, t_flags flags);
int		print_pointer_with_flags(va_list args, t_flags flags);

#endif
