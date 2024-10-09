//
// Created by Fedor Evgr on 04/10/2024.
//

#ifndef LAB3_SRC_C_VECTOR_H
#define LAB3_SRC_C_VECTOR_H

#include "Codes.h"
#include <stdlib.h>

typedef struct
{
    double *values;
    unsigned long *indexes;
    unsigned long valueAmount;
    unsigned long length;
} RareVector;

typedef struct
{
    double *values;
    unsigned long length;
} BasicVector;

ErrorCode
vectorFill(RareVector *rareVector);
ErrorCode
vectorAddElement(RareVector *, double value, size_t);

ErrorCode
vectorCreate(RareVector *, size_t size);
void
vectorFree(RareVector);

RareVector *
vectorBasicToRare(BasicVector);
BasicVector *
vectorRareToBasic(RareVector);

#endif //LAB3_SRC_C_VECTOR_H
