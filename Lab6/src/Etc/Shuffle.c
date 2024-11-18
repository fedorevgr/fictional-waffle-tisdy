#include "Shuffle.h"

#define OK 0
#define ARGUMENT_ERR 1

static int swap(void *first_elem, void *second_elem, size_t element_size);

int
shuffle(void *array, size_t size, size_t element_size, double shuffleFactor)
{
    if (shuffleFactor > 1)
        return ARGUMENT_ERR;

    int rc = OK;

    char *pointer_to_array = (char *)array;
    size_t rounds = (size_t) ((double) size * shuffleFactor);

    for (size_t i = size - 1, k = 0; rc == OK && i > 0 && k < rounds; --i)
    {
        size_t j = rand() % (i + 1);
        rc = swap(pointer_to_array + j * element_size, pointer_to_array + i * element_size, element_size);
    }

    return rc;
}
static int swap(void *first_elem, void *second_elem, size_t element_size)
{
    int rc = OK;

    if (!first_elem || !second_elem)
        rc = ARGUMENT_ERR;

    unsigned char *pointer_to_first_elem = (unsigned char *)first_elem;
    unsigned char *pointer_to_second_elem = (unsigned char *)second_elem;

    for (size_t i = 0; rc == OK && i < element_size; ++i)
    {
        unsigned char temp = pointer_to_first_elem[i];
        pointer_to_first_elem[i] = pointer_to_second_elem[i];
        pointer_to_second_elem[i] = temp;
    }

    return rc;
}