
#ifndef LAB3_SRC_C_INPUT_H
#define LAB3_SRC_C_INPUT_H

#include "Codes.h"
#include <assert.h>

#define MAX_BUFFER_LENGTH 50

typedef enum
{
    INPUT_OK,
    INPUT_E_LENGTH,
    INPUT_E_READ,
    INPUT_E_EMPTY,
    INPUT_E
}
    InputError;

InputError
inputDouble(double *);
InputError
inputUnsigned(unsigned long *n);
InputError
inputSigned(long *n);
InputError
inputString(char *buffer);

#endif //LAB3_SRC_C_INPUT_H
