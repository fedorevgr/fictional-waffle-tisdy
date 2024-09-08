
#include "output.h"
#include "stdio.h"


void print(Number number)
{
#ifndef EXP_PRINT
    String buffer = "";
    printf("Sign:           %c\n", number.sign == 0 ? '+' : '-');
    printf("Value:          %s\n", valueToStr(number, buffer));
    printf("Exponent:       %d\n", number.exponent);
#else
    String buffer = "";
    printf("%c0.%se%d\n", number.sign == 0 ? '+' : '-', valueToStr(number, buffer), number.exponent);
#endif
}
