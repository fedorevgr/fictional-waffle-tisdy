
#include "output.h"
#include "stdio.h"


void print(Number number)
{
    String buffer = "";
    printf("Sign:           %c\n", number.sign == 0 ? '+' : '-');
    printf("Value:          %s\n", valueToStr(number, buffer));
    printf("Exponent:       %d\n", number.exponent);
}
