//
// Created by Fedor Evgr on 04/10/2024.
//

#include "objects/Vector.h"
#include "Arrays.h"

ErrorCode
vectorFill(RareVector *rareVector)
{

}

ErrorCode
vectorAddElement(RareVector *vector, double value, size_t toIndex)
{
    void *buf, *buf2;
    buf = realloc(vector->values, (vector->valueAmount + 1) * sizeof(*vector->values));
    buf2 = realloc(vector->indexes, (vector->valueAmount + 1) * sizeof(*vector->values));

    if (!buf || !buf2)
        return ERROR_MEMORY;

    vector->values = buf;
    vector->indexes = buf2;

    size_t i = vector->length - 1;
    for (; i > 0 && i != toIndex; i--);

    arrayInsert(
        vector->values,
        &vector->valueAmount,
        sizeof(*vector->values),
        &value, i
        );

    size_t decoy = vector->valueAmount;
    arrayInsert(
        vector->indexes,
        &decoy,
        sizeof(*vector->indexes),
        &toIndex, i
    );

    return OK;
}

#define ARRAY_INIT_SIZE 1
ErrorCode vectorCreate(RareVector *vector, size_t size)
{
    if (size < 1)
        return ERROR;

    vector->values = calloc(ARRAY_INIT_SIZE, sizeof(double));
    vector->indexes = calloc(ARRAY_INIT_SIZE, sizeof(size_t));
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
