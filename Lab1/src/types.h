#ifndef LAB1_SRC_TYPES_H
#define LAB1_SRC_TYPES_H

#define MAX_STRING_LENGTH   60
#define VALUE_LENGTH_LIMIT_FIRST 35
#define VALUE_LENGTH_LIMIT  40
#define EXPONENT_LIMIT      99999

#define ABS(number)  ((number < 0) ? -number : number)
#define LENGTH_LIMIT(number) ((number.posFirst) ? VALUE_LENGTH_LIMIT_FIRST : VALUE_LENGTH_LIMIT)

typedef char String[MAX_STRING_LENGTH + 1];

typedef struct NumberStruct
{
    bool sign;
    int exponent;
    int value[VALUE_LENGTH_LIMIT + 1];
    int valueLength;
    int mathStatus;
    bool posFirst;
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
    ERROR_RESULT,
    ERROR_LIMITS
} ExitCode;

#define AND &&
#define OR ||
#define NOT !

#endif //LAB1_SRC_TYPES_H
