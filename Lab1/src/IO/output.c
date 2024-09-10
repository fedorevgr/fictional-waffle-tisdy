
#include "output.h"
#include "stdio.h"
#include "../mathing.h"

void print(Number number)
{
#ifndef EXP_PRINT
    String buffer = "";
    printf("Sign:           %c\n", number.sign == 0 ? '+' : '-');
    printf("Value:          %s\n", valueToStr(number, buffer));
    printf("Exponent:       %d\n", number.exponent);
#else
    String buffer = "";
    switch ((MErrors) number.mathStatus)
    {
        case M_OK:
            printf("%c0.%se%d\n", number.sign == 0 ? '+' : '-', valueToStr(number, buffer), number.exponent);
            break;
        case M_ERR_INF: printf("INF\n");
            break;
        case M_ERR_ZERO: printf("ZERO\n");
            break;
        case M_ERR_LENGTH: printf("OVERFLOW\n");
            break;
    }

#endif
}


void showResult(ExitCode code, Number number)
{
    switch (code)
    {
        case OK: print(number);
            break;
        case ERROR: printf("ERROR: input string error\n");
            break;
        case ERROR_VALIDATION: printf("ERROR: input number error\n");
            break;
        case ERROR_RESULT:
            break;
        case ERROR_LIMITS: printf("ERROR: input number limits error\n");
            break;
    }
}