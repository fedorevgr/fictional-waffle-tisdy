#include <stdlib.h>
#include "Types.h"

void
setSign(Number *number, char sign)
{
    number->sign = sign;
}

void
setValue(Number *number, char *value, const char *valueEnd)
{
    int length = 0;
    for (; value != valueEnd; value++, length++)
        (*number).value[length] = *value - '0';
    number->valueLength = length;
}

void
setExponent(Number *number, int exponent)
{
    number->exponent = exponent;
}

char *
valueToStr(Number number, char *buffer)
{
    int i = 0;
    if (number.value[i] == 0)
        buffer[i++] = '0';
    else
        for (; i < number.valueLength; i++)
            buffer[i] = number.value[i] + '0';

    buffer[i] = '\0';

    return buffer;
}
