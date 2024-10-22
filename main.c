#include <stdio.h>
#include "files/include/ft_printf_bonus.h"

int    main(void)
{
    /*
    int a;
	char *str = "cositas";
    
    a = ft_printf("Hello, %s! \n %u / %d / %d // %p // %x - %X\n", str, 3147483647, -42, -2147483648, str, 65436, 56456);
    ft_printf("ft_printf: %d\n", a);
    a = printf("Hello, %s! \n %u / %d / %d // %p // %x - %X\n", str, 3147483647, -42, -2147483648, str, 65436, 56456);
    printf("printf: %d\n\n\n", a);

    a = ft_printf("%.c", 'a');
    ft_printf("ft_printf: %d\n", a);
    a = printf("%.c", 'a');
    printf("printf: %d\n\n\n", a);

    a = ft_printf("%-5%");
    ft_printf("ft_printf: %d\n", a);
    a = printf("%-5%");
    printf("printf: %d\n\n\n", a);
    printf("\n------------------------------------\n");
    a = ft_printf("%-15%# +d \n", 'c');
    a = ft_printf("% 7.5d# +d \n", 512);
    a = ft_printf("%- 10d# +d \n", 512);
    a = ft_printf("%0 7d# +d \n", 512);
    a = ft_printf("%015s# +d \n", "holahola");
    ft_printf("printf: %d\n\n\n", a);

    a = printf("%-15%# +d \n", 'c');
    a = printf("% 7.5d# +d \n", 512);
    a = printf("%- 10d# +d \n", 512);
    a = printf("%0 7d# +d \n", 512);
    a = printf("%015s# +d \n", "holahola");
    printf("printf: %d\n\n\n", a);
    printf("\n------------------------------------\n");*/

    /*
    int num = 42;
    unsigned int unum = 3000;
    float fnum = 3.14159;
    char *str = "Hola";
    void *ptr = &num;

    // 1. Flags con %d (entero con signo)
    printf("1. |%+08d|\n", num);     // Signo siempre, relleno con ceros, ancho mínimo de 8
    printf("2. |%-8d|\n", num);      // Alineación a la izquierda, ancho mínimo de 8
    printf("3. |% 8d|\n", num);      // Espacio para positivo, ancho mínimo de 8
    ft_printf("1. |%+08d|\n", num);     // Signo siempre, relleno con ceros, ancho mínimo de 8
    ft_printf("2. |%-8d|\n", num);      // Alineación a la izquierda, ancho mínimo de 8
    ft_printf("3. |% 8d|\n", num);
    
    printf("\n------------------------------------\n");
    // 2. Flags con %u (entero sin signo)
    printf("4. |%08u|\n", unum);     // Relleno con ceros, ancho mínimo de 8
    printf("5. |%-8u|\n", unum);     // Alineación a la izquierda, ancho mínimo de 8

    ft_printf("4. |%08u|\n", unum);     // Relleno con ceros, ancho mínimo de 8
    ft_printf("5. |%-8u|\n", unum);     // Alineación a la izquierda, ancho mínimo de 8
    
    printf("\n------------------------------------\n");
    // 3. Flags con %x (hexadecimal en minúscula)
    printf("6. |%#08x|\n", num);     // Prefijo 0x, relleno con ceros, ancho mínimo de 8
    printf("7. |%-#8x|\n", num);     // Prefijo 0x, alineación a la izquierda, ancho mínimo de 8
    ft_printf("6. |%#08x|\n", num);     // Prefijo 0x, relleno con ceros, ancho mínimo de 8
    ft_printf("7. |%-#8x|\n", num);
    
    printf("\n------------------------------------\n");
    // 5. Flags con %s (cadena de caracteres)
    printf("11. |%-10s|\n", str);    // Alineación a la izquierda, ancho mínimo de 10
    printf("12. |%.3s|\n", str);     // Precisión de 3 caracteres, limita la cadena
    ft_printf("11. |%-10s|\n", str);    // Alineación a la izquierda, ancho mínimo de 10
    ft_printf("12. |%.3s|\n", str);
    
    printf("\n------------------------------------\n");
    // 6. Flags con %p (puntero)
    printf("13. |%20p|\n", ptr);     // Ancho mínimo de 20
    printf("14. |%-20p|\n", ptr);    // Alineación a la izquierda, ancho mínimo de 20
    ft_printf("13. |%20p|\n", ptr);     // Ancho mínimo de 20
    ft_printf("14. |%-20p|\n", ptr); 

    int a;
    a = ft_printf("%7.5s", "bombastic");
    ft_printf("LEN: %d\n", a);
    a = printf("%7.5s", "bombastic");
    printf("LEN: %d\n", a);*/

/*
    int a = 42, b = -56;
    unsigned int c = 12345, d = 67890;
    float e = 3.14159, f = -2.71828;
    char *str1 = "Hola", *str2 = "Mundo";
    void *ptr1 = &a, *ptr2 = &b;

    // 1. Múltiples enteros con diferentes flags
    printf("1. |%+8d| |%-8d| |%08d|\n", a, b, a); 
    ft_printf("1. |%+8d| |%-8d| |%08d|\n", a, b, a);
    printf("\n------------------------------------\n");
    
    // 2. Enteros con signo y sin signo combinados
    printf("2. |%#8x| |%#8X| |%08u| |%-8u|\n", a, b, c, d);
    ft_printf("2. |%#8x| |%#8X| |%08u| |%-8u|\n", a, b, c, d);
    printf("\n------------------------------------\n");
    
    // 3. Números flotantes con ancho mínimo y precisión, mezclados con enteros
    printf("3. |%8d| |%08d|\n", a, b); 
    ft_printf("3. |%8d| |%08d|\n", a, b); 
    printf("\n------------------------------------\n");
    
    // 4. Cadenas de caracteres combinadas con precisión y ancho mínimo
    printf("4. |%-10s| |%.3s| |%10s| |%-8.5s|\n", str1, str2, str1, str2); 
    ft_printf("4. |%-10s| |%.3s| |%10s| |%-8.5s|\n", str1, str2, str1, str2);
    printf("\n------------------------------------\n"); 
    
    // 5. Punteros combinados con diferentes anchos mínimos
    printf("5. |%20p| |%-20p|\n", ptr1, ptr2); 
    ft_printf("5. |%20p| |%-20p|\n", ptr1, ptr2); 
    printf("\n------------------------------------\n");
    
    // 6. Combinación de enteros, flotantes y hexadecimales en una sola línea
    printf("6. |%+10d| |%-#8x| |%-#8.3X|\n", b, a, d);
    ft_printf("6. |%+10d| |%-#8x| |%-#8.3X|\n", b, a, d);*/


/*
    int a = 2147483647, b = -2147483648;
    unsigned int c = 0, d = 4294967295u;
    char *str1 = "EdgeCaseTesting", *str2 = "OvercomplicatedOutput";
    void *ptr1 = &a, *ptr2 = NULL;
    int num;

    // Ejemplo 1: Máximos y mínimos de enteros con precisión y alineación extrema
    num = printf("1. |%+30.20d| |%-30.20d|\n", a, b);
    printf("LEN: %d\n", num);
    num = ft_printf("1. |%+30.20d| |%-30.20d|\n", a, b);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 2: Hexadecimales máximos y mínimos con relleno de ceros y prefijo
    num = printf("2. |%0#40.30x| |%-#40.30x|\n", a, b);
    printf("LEN: %d\n", num);
    num = ft_printf("2. |%0#40.30x| |%-#40.30x|\n", a, b);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 3: Sin signo, cadena truncada y puntero nulo con anchos variados
    num = printf("3. |%030u| |%.5s| |%-20p|\n", d, str1, ptr2);
    printf("LEN: %d\n", num);
    num = ft_printf("3. |%030u| |%.5s| |%-20p|\n", d, str1, ptr2);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 4: Enteros en hexadecimal con precisión elevada y cadenas con alineación mixta
    num = printf("4. |%#50.45x| |%-20s| |%.10s|\n", d, str2, str1);
    printf("LEN: %d\n", num);
    num = ft_printf("4. |%#50.45x| |%-20s| |%.10s|\n", d, str2, str1);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 5: Cadena con ancho extremo, puntero y hexadecimal con mínima precisión y prefijo
    num = printf("5. |%-60.15s| |%25.5p| |%#-30.4x|\n", str2, ptr1, c);
    printf("LEN: %d\n", num);
    num = ft_printf("5. |%-60.15s| |%25.5p| |%#-30.4x|\n", str2, ptr1, c);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 6: Hexadecimal sin signo con precisión, entero negativo con ancho y precisión extremos
    num = printf("6. |%-#50.45x| |%+60.55d|\n", d, b);
    printf("LEN: %d\n", num);
    num = ft_printf("6. |%-#50.45x| |%+60.55d|\n", d, b);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 7: Sin signo con relleno de ceros, cadena truncada y puntero con precisión
    num = printf("7. |%040u| |%.8s| |%20.10p|\n", d, str1, ptr2);
    printf("LEN: %d\n", num);
    num = ft_printf("7. |%040u| |%.8s| |%20.10p|\n", d, str1, ptr2);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 8: Hexadecimal, puntero y sin signo con prefijo y precisión elevada
    num = printf("8. |%-#60.55x| |%30.15p| |%+050.40u|\n", a, ptr1, d);
    printf("LEN: %d\n", num);
    num = ft_printf("8. |%-#60.55x| |%30.15p| |%+050.40u|\n", a, ptr1, d);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 9: Enteros y hexadecimales con relleno de ceros, ancho y precisión altos
    num = printf("9. |%020.18d| |%#020.18x| |%-#020.18x|\n", a, b, d);
    printf("LEN: %d\n", num);
    num = ft_printf("9. |%020.18d| |%#020.18x| |%-#020.18x|\n", a, b, d);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    // Ejemplo 10: Cadena truncada, entero con signo y hexadecimal con ancho amplio
    num = printf("10. |%.4s| |%+80.70d| |%-#80.75x|\n", str2, b, a);
    printf("LEN: %d\n", num);
    num = ft_printf("10. |%.4s| |%+80.70d| |%-#80.75x|\n", str2, b, a);
    printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");*/

    int num;
    
    num = printf("%20.5d", -1024);
    printf("LEN: %d\n", num);
    num = ft_printf("%20.5d", -1024);
    ft_printf("LEN: %d\n", num);
    printf("\n------------------------------------\n");

    return (0);
}
