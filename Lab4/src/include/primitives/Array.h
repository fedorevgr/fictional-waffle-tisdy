#ifndef LAB4_SRC_C_PRIMITIVES_ARRAY_H
#define LAB4_SRC_C_PRIMITIVES_ARRAY_H

#include "primitives/StackElement.h"
#include "stdlib.h"

typedef struct array_
{
    size_t length;
    StackElement elements[];
} Array;

Array *arrayCreate(size_t length);
void arrayFree(Array *);

#endif //LAB4_SRC_C_PRIMITIVES_ARRAY_H
