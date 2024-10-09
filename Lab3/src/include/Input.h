//
// Created by Fedor Evgr on 05/10/2024.
//

#ifndef LAB3_SRC_C_INPUT_H
#define LAB3_SRC_C_INPUT_H

#include "Codes.h"
#include <assert.h>

#define MAX_BUFFER_LENGTH 20
typedef enum
{
    INPUT_OK,
    INPUT_E_LENGTH,
    INPUT_E_READ,
    INPUT_E_EMPTY,
    INPUT_E
} InputError;

InputError inputDouble(double *);
InputError inputUnsigned(unsigned long *n);
InputError inputSigned(long *n);


#endif //LAB3_SRC_C_INPUT_H
