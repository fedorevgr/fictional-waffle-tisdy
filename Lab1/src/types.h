#ifndef LAB1_SRC_TYPES_H
#define LAB1_SRC_TYPES_H

#include "mathing.h"

#define MAX_STRING_LENGTH 60 // TODO: switch to 60

typedef char String[MAX_STRING_LENGTH + 1];

typedef struct NumberStruct
{
    char sign;
    int exponent;
    char value[NUM_LENGTH];
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
    ERROR_VALIDATION
} ExitCode;

#define AND &&
#define OR ||
#define NOT !

#endif //LAB1_SRC_TYPES_H
