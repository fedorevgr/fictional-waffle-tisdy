#ifndef LAB1_SRC_TYPES_H
#define LAB1_SRC_TYPES_H

#include "mathing.h"

#define MAX_STRING_LENGTH   60
#define VALUE_LENGTH_LIMIT  40
#define EXPONENT_LIMIT      99999

#define ABS(number)  ((number < 0) ? -number : number)

typedef char String[MAX_STRING_LENGTH + 1];

typedef struct NumberStruct
{
    bool sign;
    int exponent;
    int value[VALUE_LENGTH_LIMIT + 1];
    int valueLength;
} Number;

void
setSign(Number *number, char sign);

void
setValue(Number *number, char *value, const char *valueEnd);

void
setExponent(Number *number, int exponent);

char *
valueToStr(Number number, char *buffer);

typedef enum ExitCode
{
    OK,
    ERROR,
    ERROR_VALIDATION,
    ERROR_RESULT
} ExitCode;

#define AND &&
#define OR ||
#define NOT !

#endif //LAB1_SRC_TYPES_H
