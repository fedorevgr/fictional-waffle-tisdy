//
// Created by Fedor Evgr on 04/10/2024.
//

#include "objects/Vector.h"
#include "Arrays.h"
#include "simple/PrimitiveInput.h"

ErrorCode
vectorAddElement(RareVector *vector, double value, size_t toIndex)
{
    if (toIndex > vector->length)
        return ERROR;

    size_t i = 0;
    for (; vector->indexes[i] < toIndex && i < vector->valueAmount; i++);

    size_t decoy = vector->valueAmount;
    arrayInsert(
        vector->values,
        &vector->valueAmount,
        sizeof(*vector->values),
        &value, i
        );

    arrayInsert(
        vector->indexes,
        &decoy,
        sizeof(*vector->indexes),
        &toIndex, i
    );

    return OK;
}

double
rareVectorGet(const RareVector v, size_t i)
{
    for (size_t I = 0; I < v.valueAmount; ++I)
    {
        if (v.indexes[I] == i)
            return v.values[I];
    }
    return 0;
}

#define ARRAY_INIT_SIZE 1
ErrorCode vectorCreate(RareVector *vector, size_t size)
{
    if (size < 1)
        return ERROR;

    vector->values = calloc(ARRAY_INIT_SIZE * size, sizeof(double));
    vector->indexes = calloc(ARRAY_INIT_SIZE * size, sizeof(size_t));
    vector->length = size;
    vector->valueAmount = 0;

    return OK;
}

void
vectorFree(RareVector vector)
{
    free(vector.values);
    free(vector.indexes);
}

ErrorCode
basicVectorCreate(BasicVector *vector, size_t length)
{
    if (! length)
        return ERROR;

    vector->length = length;
    vector->values = calloc(length, sizeof(double));

    if (vector->values)
        return OK;
    else
        return ERROR_MEMORY;
}

void
vectorBasicToRare(RareVector *rv, BasicVector bv)
{
    for (size_t i = 0; i < bv.length; ++i)
        vectorAddElement(rv, bv.values[i], i);
}

#include <time.h>
void
fillRandomBasicVector(BasicVector vector, size_t percentile)
{
    size_t amount = vector.length * percentile / 100;
    for (size_t i = 0; i < amount; ++i)
        vector.values[i] = 1;

    randomizeArrayOfDoubles(vector.values, vector.length);
}

void
basicVectorFree(BasicVector *vector)
{
    free(vector->values);
    vector->values = NULL;
    vector->length = 0;
}

