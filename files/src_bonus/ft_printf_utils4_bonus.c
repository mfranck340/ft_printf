
#include "../include/ft_printf_bonus.h"
#include <stdio.h>

int	print_n_string(char *str, unsigned int n)
{
	int		n_ret;

	n_ret = 0;
	while (str && n--)
	{
		ft_putchar_fd(*str, 1);
		str++;
		n_ret++;
	}
	return (n_ret);
}

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

int	print_format_flags(va_list args, t_flags flags)
{
	char *str;
	int n_aux;
	int	number;
	unsigned int hex_number;
	void	*pointer;
    int is_null;


	int	n_str;

	n_str = 0;
	if (flags.type == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	else if (flags.type == 'c')
	{
		if (flags.minus)
		{
			n_str += print_char(va_arg(args, int));
			while (flags.width-- > 1)
				n_str += print_char(' ');
		}
		else
		{
			while (flags.width-- > 1)
				n_str += print_char(' ');
			n_str += print_char(va_arg(args, int));
		}
	}
	else if (flags.type == 's')
	{
		str = va_arg(args, char *);
		n_str = ft_strlen(str);
		if (flags.dot && flags.precision < n_str)
			n_str = flags.precision;
		n_aux = n_str;
		if (flags.minus)
		{
			if (!str && (flags.dot == 0 || flags.precision >= 6))
			{
				print_n_string("(null)", 6);
				n_str += 6;
				n_aux = 6;

			}
			else
				print_n_string(str, n_aux);
			while (flags.width-- > n_aux)
				n_str += print_char(' ');
		}
		else
		{
			if (!str && (flags.dot == 0 || flags.precision >= 6))
			{
				while (flags.width-- > 6)
					n_str += print_char(' ');
				print_n_string("(null)", 6);
				n_str += 6;
			}
			else
			{
				while (flags.width-- > n_aux)
					n_str += print_char(' ');
				print_n_string(str, n_aux);
			}
		}
	}
	else if (flags.type == 'd' || flags.type == 'i')
	{
		number = va_arg(args, int);
		str = ft_itoa(number);
		n_str = ft_strlen(str);
		n_aux = n_str;
        is_null = 0;
        if (number == 0 && flags.dot && flags.precision == 0)
            is_null = 1;
		if (flags.zero && flags.dot == 0 && flags.minus == 0)
		{
			if (number < 0)
				print_char('-');
			else if (number >= 0 && flags.plus)
			{
				print_char('+');
				n_str++;
				n_aux++;
			}
			else if (flags.space)
			{
				print_char(' ');
				n_str++;
				n_aux++;
			}
			while (flags.width-- > n_aux)
				n_str += print_char('0');
			if (number < 0)
				print_string(str + 1);
			else
				print_string(str);
		}
		else if (flags.minus)
		{
			if (number < 0)
			{
				print_char('-');
				n_aux--;
			}
			else if (number >= 0 && flags.plus)
			{
				print_char('+');
				n_str++;
				n_aux++;
			}
			else if (flags.space)
			{
				print_char(' ');
				n_str++;
				n_aux++;
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
			else if (number < 0)
				print_string(str + 1);
			else
				print_string(str);
			n_aux = n_str;
			while (flags.width-- > n_aux)
				n_str += print_char(' ');
		}
		else
		{
			if (number < 0 || flags.plus || flags.space)
			{
				if (flags.dot && flags.precision > n_aux)
				{
					if (flags.width > flags.precision + 1)
						while (flags.width-- > flags.precision + 1)
							n_str += print_char(' ');
				}
				else if (number < 0)
				{
					if (flags.width > n_aux)
						while (flags.width-- > n_aux)
							n_str += print_char(' ');
				}
				else
				{
					if (flags.width > n_aux + 1)
						while (flags.width-- > n_aux + 1)
							n_str += print_char(' ');
				}
			}
			else
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
			if (number < 0)
			{
				print_char('-');
				if (flags.precision > n_aux - 1)
					while (flags.precision-- > n_aux - 1)
						n_str += print_char('0');
			}
			else
			{
				if (flags.plus)
				{
					print_char('+');
					n_str++;
				}
				else if (flags.space)
				{
					print_char(' ');
					n_str++;
				}
				if (flags.precision > n_aux)
					while (flags.precision-- > n_aux)
						n_str += print_char('0');
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
		}
		free(str);
	}
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
		if (flags.zero && flags.dot == 0 && flags.minus == 0)
		{
			if (flags.hashtag && hex_number != 0)
			{
				print_char('0');
				print_char(flags.type);
				n_str += 2;
				n_aux += 2;
			}
			while (flags.width-- > n_aux)
				n_str += print_char('0');
			if (flags.type == 'x')
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
			if (flags.type == 'x')
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
						while (flags.width-- > n_aux)
							n_str += print_char(' ');
				}
			}
			if (flags.precision > n_aux)
				while (flags.precision-- > n_aux)
					n_str += print_char('0');
			if (flags.type == 'x')
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
