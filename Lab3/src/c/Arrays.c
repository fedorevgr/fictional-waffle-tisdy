//
// Created by Fedor Evgr on 06/10/2024.
//

#include "Arrays.h"
#include <string.h>

ErrorCode
arrayInsert(void *array, size_t *length, const size_t size, const void *element, size_t index)
{
    if (index >= *length)
        index = *length;

    for (size_t i = *length; i > 0 && index != i; i--)
    {
        memcpy((char *) array + (i * size), (char *) array + (i - 1) * size, size);
    }

    memcpy(array + index * size, element, size);
    *length += 1;

    return OK;
}

ErrorCode
arrayFind(const void *array, const size_t length, const size_t size, const void *element, size_t *result)
{
    ErrorCode ec = ERROR;

    for (size_t i = 0; i < length && ec == ERROR; i++)
    {
        if (memcmp(array + i * size, element, size) == 0)
        {
            ec = OK;
            *result = i;
        }
    }
    return ec;
}

#include <time.h>

void randomizeArrayOfDoubles(double *array, size_t length)
{
    srand(time(NULL));
    double tmp;
    size_t J;
    for (size_t I = 0; I < length; ++I)
    {
        J = rand() % length;
        tmp = array[J];
        array[J] = array[I];
        array[I] = tmp;
    }
}