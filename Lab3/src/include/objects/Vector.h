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
vectorAddElement(RareVector *, double value, size_t);
double
rareVectorGet(RareVector, size_t);

ErrorCode
vectorCreate(RareVector *, size_t size);
void
vectorFree(RareVector);

void
vectorBasicToRare(RareVector *rv, BasicVector bv);

ErrorCode
basicVectorCreate(BasicVector *vector, size_t length);
void
basicVectorFree(BasicVector *vector);

void
fillRandomBasicVector(BasicVector vector, size_t percentile);

#endif //LAB3_SRC_C_VECTOR_H
