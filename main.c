#include <stdio.h>
#include "files/include/ft_printf_bonus.h"

int    main(void)
{
    int a;
	char *str = "cositas";
    /*
    a = ft_printf("Hello, %s! \n %u / %d / %d // %p // %x - %X\n", str, 3147483647, -42, -2147483648, str, 65436, 56456);
    ft_printf("ft_printf: %d\n", a);
    a = printf("Hello, %s! \n %u / %d / %d // %p // %x - %X\n", str, 3147483647, -42, -2147483648, str, 65436, 56456);
    printf("printf: %d\n\n\n", a);*/

    a = ft_printf("%7.7s%7.7s", "hello", "world");
    ft_printf("ft_printf: %d\n", a);
    a = ft_printf(" %.s ", "-");
    ft_printf("ft_printf: %d\n", a);
    a = printf(" %.s ", "-");
    printf("printf: %d\n\n\n", a);
    printf("\n------------------------------------\n");
    a = printf("%+u\n", 3432);
    a = printf("%+d\n", 3432);
    a = printf("%-15%# +d \n", 'c');
    a = printf("%15.4d# +d \n", 512);
    a = printf("%-15.2d# +d \n", 512);
    a = printf("%015d# +d \n", 512);
    a = printf("%015s# +d \n", "holahola");
    printf("printf: %d\n\n\n", a);

    a = ft_printf("|%-0# +10.8%|\n", 255);
    ft_printf("ft_printf: %d\n", a);
    a = printf("|%-0# +.8%|\n", 255);
    printf("printf: %d\n\n\n", a);

    return (0);
}
