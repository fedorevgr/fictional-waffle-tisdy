#include "mathing.h"

#define SWAP(a, b)  do { \
        a ^= b; \
        b ^= a; \
        a ^= b; \
} while(0)

void
reverseArray_(int *array, int length)
{
    for (int i = 0; i < length / 2; i++)
        SWAP(array[i], array[length - i - 1]);
}

MErrors
checkResult(Number a, Number b)
{
    if (a.exponent + b.exponent - (a.value[0] * b.value[0] < 10) > EXPONENT_LIMIT)
        return M_ERR_INF;

    if (a.exponent + b.exponent - (a.value[0] * b.value[0] < 10) < -EXPONENT_LIMIT)
        return M_ERR_ZERO;

    return M_OK;
}

void
alise(int *buffer, int length) // in reversed array
{
    int tmp;
    for (int i = 0; i < length; i++)
    {
        tmp = buffer[i];
        if (tmp > 9)
            buffer[i + 1] += tmp / 10, buffer[i] = tmp % 10;
    }
}

int *cutAndRoundValue(int *buffer, int *newLength) // in reversed array
{
    if (*newLength > VALUE_LENGTH_LIMIT)
    {
        buffer += (*newLength - VALUE_LENGTH_LIMIT);
        *newLength =VALUE_LENGTH_LIMIT;
        if (*(buffer - 1) >= 5)
        {
            *buffer += 1;
            alise(buffer, VALUE_LENGTH_LIMIT);
            *newLength += (buffer[VALUE_LENGTH_LIMIT] != 0);
        }
    }
    for (; *buffer == 0; buffer++, *newLength -= 1);
    return buffer;
}

void copy(Number *number, const int *buffer, const int length)
{
    for (int i = 0; i < length; i++)
        number->value[i] = buffer[i];
}

ExitCode
multiplyValues_(Number number1, Number number2, Number *buffer)
{
    int newNumber[VALUE_LENGTH_LIMIT * 2 + 1] = { 0 };
    int newNumberLength = VALUE_LENGTH_LIMIT * 2;

    reverseArray_(number1.value, number1.valueLength);
    reverseArray_(number2.value, number2.valueLength);

    int remainder = 0, temp;
    for (int lowerDigit = 0; lowerDigit < number2.valueLength; lowerDigit++)
    {
        remainder = 0;
        for (int upperDigit = 0; upperDigit < number1.valueLength; upperDigit++)
        {
            temp = number1.value[upperDigit] * number2.value[lowerDigit];
            newNumber[lowerDigit + upperDigit] += temp % 10 + remainder;
            remainder = temp / 10;
            alise(newNumber, newNumberLength);
        }

        newNumber[lowerDigit + number1.valueLength] += remainder;
        alise(newNumber, newNumberLength);
    }
    newNumberLength = number2.valueLength + number1.valueLength - (remainder == 0);
    int *number = cutAndRoundValue(newNumber, &newNumberLength);

    copy(buffer, number, newNumberLength);
    buffer->valueLength = newNumberLength;
    buffer->exponent -= (remainder == 0);

    reverseArray_(buffer->value, buffer->valueLength);

    return OK;
}

ExitCode
multiplyExponents_(Number num1, Number num2, Number *buffer)
{
    buffer->exponent += num1.exponent + num2.exponent;
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
    result->mathStatus = checkResult(numberA, numberB);

    if (result->mathStatus == M_OK)
    {
        multiplyValues_(numberA, numberB, result);
        multiplyExponents_(numberA, numberB, result);
        multiplySigns_(numberA, numberB, result);
    }

    return OK;
}

