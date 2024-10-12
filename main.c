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
    a = ft_printf(" %+d ", 0);
    ft_printf("ft_printf: %d\n", a);
    a = printf(" %+d ", 0);
    printf("printf: %d\n\n\n", a);
    printf("\n------------------------------------\n");
    a = printf("%+u\n", 3432);
    a = printf("%+d\n", 3432);
    printf("%020p\n", str);
    printf("%-20p\n", str);
    printf("%20p\n", str);
    a = printf("%-15%# +d \n", 'c');
    a = printf("% 7.5d# +d \n", 512);
    a = printf("%- 10d# +d \n", 512);
    a = printf("%0 7d# +d \n", 512);
    a = printf("%015s# +d \n", "holahola");
    printf("printf: %d\n\n\n", a);

    a = ft_printf("|%-0# +10.8%|\n", 255);
    ft_printf("ft_printf: %d\n", a);
    a = printf("|%-0# +.8%|\n", 255);
    printf("printf: %d\n\n\n", a);

    return (0);
}
