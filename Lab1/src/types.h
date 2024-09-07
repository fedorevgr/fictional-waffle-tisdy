#ifndef LAB1_SRC_TYPES_H
#define LAB1_SRC_TYPES_H

#include "mathing.h"

#define MAX_STRING_LENGTH 60 // TODO: switch to 60


typedef char String[MAX_STRING_LENGTH + 1];

typedef struct NumberStruct {
    char sign;
    int exponent;
    char value[NUM_LENGTH];
} Number;

typedef enum ExitCode {
    OK,
    ERROR,
    ERROR_VALIDATION
} ExitCode;

#define AND &&
#define OR ||
#define NOT !

#endif //LAB1_SRC_TYPES_H
