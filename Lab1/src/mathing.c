#include "mathing.h"

#define SWAP(a, b)  do { \
        a ^= b; \
        b ^= a; \
        a ^= b; \
} while(0)

void
reverseArray_(int *array, int length)
{
    for (int i = 0; i * 2 < length; i++)
        SWAP(array[i], array[length - i - 1]);
}

ExitCode
checkResult(Number a, Number b)
{
    if (a.valueLength + b.valueLength - (a.value[0] * b.value[0] < 10) > VALUE_LENGTH_LIMIT)
        return ERROR_RESULT;

    if (ABS(a.exponent + b.exponent) > EXPONENT_LIMIT)
        return ERROR_RESULT;

    return OK;
}

ExitCode
multiplyValues_(Number number1, Number number2, Number *buffer)
{
    reverseArray_(number1.value, number1.valueLength);
    reverseArray_(number2.value, number2.valueLength);

    int remainder = 0, temp;
    for (int lowerDigit = 0; lowerDigit < number2.valueLength; lowerDigit++)
    {
        for (int upperDigit = 0; upperDigit < number1.valueLength; upperDigit++)
        {
            temp = number1.value[upperDigit] * number2.value[lowerDigit];
            buffer->value[lowerDigit + upperDigit] += temp % 10 + remainder; // TODO: think
            remainder = temp / 10;
        }

        buffer->value[lowerDigit + number1.valueLength] += remainder;
    }

    buffer->valueLength = number2.valueLength + number1.valueLength - (remainder == 0);

    reverseArray_(buffer->value, buffer->valueLength);

    return OK;
}

ExitCode
multiplyExponents_(Number num1, Number num2, Number *buffer)
{
    buffer->exponent = num1.exponent + num2.exponent;
    return OK;
}
ExitCode
multiplySigns_(Number num1, Number num2, Number *buffer)
{
    buffer->sign = num1.sign ^ num2.sign;
    return OK;
}

ExitCode
multiply(Number numberA, Number numberB, Number *result)
{
    if (checkResult(numberA, numberB) != OK)
        return ERROR_RESULT;

    multiplyValues_(numberA, numberB, result);
    multiplyExponents_(numberA, numberB, result);
    multiplySigns_(numberA, numberB, result);

    return OK;
}

