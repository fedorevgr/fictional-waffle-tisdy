#include "primitives/Array.h"

Array *
arrayCreate(size_t length)
{
    Array *array = malloc(sizeof(array->length) + sizeof(StackElement) * length);
    array->length = length;

    return array;
}

void
arrayFree(Array *array)
{
    free(array);
}
