#ifndef LAB1_SRC_MATHING_H
#define LAB1_SRC_MATHING_H

#include "Types.h"

typedef enum math_errors {
    M_OK,
    M_ERR_INF,
    M_ERR_ZERO,
    M_ERR_LENGTH
} MErrors;

ExitCode
multiply(Number, Number, Number*);

#endif //LAB1_SRC_MATHING_H
