
#include "../include/ft_printf_bonus.h"
#include <stdio.h>

int	ft_numlen(unsigned int n, unsigned int base)
{
	if (n < base)
		return (1);
	else
	{
		return (1 + ft_numlen(n / base, base));
	}
}

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

void	handle_zero_flag(t_flags flags, int number, int *n_str, char *str)
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

int is_null_number(int number, t_flags flags)
{
	if (number == 0 && flags.dot && flags.precision == 0)
		return (1);
	return (0);
}

int	handle_sign(int number, t_flags flags, int *n_str)
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

void	handle_minus_flag(t_flags flags, int number, int *n_str, char *str)
{
    int n_aux;
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
	int n_aux;
	int is_null;

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

int	print_format_flags(va_list args, t_flags flags)
{
	int n_aux;
	unsigned int hex_number;
	void	*pointer;
    int is_null;

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
	{
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
		{
			if (flags.precision > n_aux)
			{
				while (flags.precision-- > n_aux)
					n_str += print_char('0');
			}
            if (is_null)
            {
                if (flags.width > 0)
                    print_char(' ');
            }
            else
			    print_unsigned(hex_number);
			n_aux = n_str;
			while (flags.width-- > n_aux)
				n_str += print_char(' ');
		}
		else
		{
			if (flags.dot && flags.precision > n_aux)
			{
				if (flags.width > flags.precision)
					while (flags.width-- > flags.precision)
						n_str += print_char(' ');
				if (flags.precision > n_aux)
					while (flags.precision-- > n_aux)
						n_str += print_char('0');
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
            if (is_null)
            {
                if (flags.width > 0)
                    print_char(' ');
            }
            else
			    print_unsigned(hex_number);
		}
	}
	else if (flags.type == 'x' || flags.type == 'X')
	{
		hex_number = va_arg(args, unsigned int);
		n_str = ft_numlen(hex_number, 16);
		n_aux = n_str;
		is_null = 0;
        if (hex_number == 0 && flags.dot && flags.precision == 0)
            is_null = 1;
		if (flags.zero && flags.dot == 0 && flags.minus == 0)
		{
			if (flags.hashtag && hex_number != 0)
			{
				print_char('0');
				print_char(flags.type);
				n_str += 2;
				n_aux += 2;
			}
			while (flags.width > n_aux)
			{
				n_str += print_char('0');
				flags.width--;
			}
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
		else if (flags.minus)
		{
			if (flags.hashtag && hex_number != 0)
			{
				print_char('0');
				print_char(flags.type);
				n_str += 2;
			}
			if (flags.precision > n_aux)
			{
				while (flags.precision-- > n_aux)
					n_str += print_char('0');
			}
			if (is_null)
            {
                if (flags.width > 0)
                    print_char(' ');
            }
            else if (flags.type == 'x')
				print_hex(hex_number, HEX_LOWER);
			else
				print_hex(hex_number, HEX_UPPER);
			n_aux = n_str;
			while (flags.width-- > n_aux)
				n_str += print_char(' ');
		}
		else
		{
			if (flags.hashtag && hex_number != 0)
			{
				if (flags.dot)
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
				print_char('0');
				print_char(flags.type);
				n_str += 2;
			}
			else
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
			if (flags.precision > n_aux)
				while (flags.precision-- > n_aux)
					n_str += print_char('0');
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
	}
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
