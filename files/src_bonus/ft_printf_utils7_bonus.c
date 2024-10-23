
#include "../include/ft_printf_bonus.h"

void	handle_sign_other(t_flags flags, int number, int *n_str, int n_aux)
{
	if (number < 0)
	{
		print_char('-');
		if (flags.precision > n_aux - 1)
			while (flags.precision-- > n_aux - 1)
				(*n_str) += print_char('0');  
	}
	else
	{
		if (flags.plus)
		{
			print_char('+');
			(*n_str)++;
		}
		else if (flags.space)
		{
			print_char(' ');
			(*n_str)++;
		}
		if (flags.precision > n_aux)
			while (flags.precision-- > n_aux)
				(*n_str) += print_char('0');
	}
}

void	handle_padding(t_flags flags, int number, int n_aux, int *n_str)
{
	if (flags.dot && flags.precision > n_aux)
	{
		if (flags.width > flags.precision + 1)
			while (flags.width-- > flags.precision + 1)
				n_str += print_char(' ');
	}
	else if (number < 0 && flags.precision < n_aux - 1)
	{
		if (flags.width > n_aux)
			while (flags.width > n_aux)
			{
				n_str += print_char(' ');
				flags.width--;
			}
	}
	else
	{
		if (flags.width > n_aux + 1)
			while (flags.width-- > n_aux + 1)
				n_str += print_char(' ');
	}
}

void	handle_padding2(t_flags flags, int n_aux, int *n_str)
{
	if (flags.dot && flags.precision > n_aux)
	{
		if (flags.width > flags.precision)
			while (flags.width-- > flags.precision)
				n_str += print_char(' ');
	}
	else
	{
		if (flags.width > n_aux)
			while (flags.width > n_aux)
			{
				n_str += print_char(' ');
				flags.width--;
			}
	}
}

void	handle_other_flag(t_flags flags, int number, int *n_str, char *str)
{
	int	n_aux;
	int	is_null;

	is_null = is_null_number(number, flags);
	n_aux = *n_str;
	if (number < 0 || flags.plus || flags.space)
		handle_padding(flags, number, n_aux, n_str);
	else
		handle_padding2(flags, n_aux, n_str);
	handle_sign_other(flags, number, n_str, n_aux);
	if (is_null)
	{
		if (flags.width > 0)
			print_char(' ');
	}
	else if (number < 0)
		print_string(str + 1);
	else
		print_string(str);
}

