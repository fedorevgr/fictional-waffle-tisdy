#include "../include/Sorting.h"

#define ASSERTIONS do { \
                    assert(ptr != NULL); \
                    assert(comp != NULL);\
                    assert(size > 0); \
                    assert(count > 0); \
                    } while (0)

#define SWAP(a, b) do {            \
                    a ^= b;         \
                    b ^= a;         \
                    a ^= b;            \
                } while (0)

SortFunc
getSort(long pos)
{
    if (pos == 1)
    {
        return choose_sort;
    }
    else if (pos == 2)
    {
        return comb_sort;
    }
    return NULL;
}

void
swap_(void *p1, void *p2, unsigned long size)
{
    char *ptr1 = p1;
    char *ptr2 = p2;

    for (int i = 0; i < size; i++, ptr1++, ptr2++)
        SWAP(*ptr1, *ptr2);
}

void
choose_sort(void *ptr, unsigned long count, unsigned long size, CompFunc comp)
{
    ASSERTIONS;

    void *max;
    void *start;
    void *end_pointer = (char *) ptr + ((count - 1) * size);
    for (int i = 0; i < count; i++, end_pointer = (char *) end_pointer - size)
    {
        max = ptr;
        start = ptr;

        for (int j = 0; j < count - i; j++, start = (char *) start + size)
        {
            if (comp(max, start) > 0)
                max = start;
        }

        if (max != end_pointer)
            swap_(max, end_pointer, size);
    }
}

#define FACTOR 1.24792
void
comb_sort(void *ptr, unsigned long count, unsigned long size, CompFunc comp)
{
    ASSERTIONS;

    unsigned long gap = count;
    int swaps = 1;
    char *array = (char *) ptr;

    while (gap > 1 OR swaps)
    {
        if (gap > 1)
            gap = (unsigned long) ((double) gap / FACTOR);

        swaps = 0;

        for (unsigned long i = 0; i + gap < count; ++i)
        {
            if (comp(array + i * size, array + (i + gap) * size) < 0)
            {
                swap_(array + i * size, array + (i + gap) * size, size);
                swaps = 1;
            }
        }
    }
}
#undef FACTOR

#include <time.h>

void shuffle(void *array, const unsigned long el_size, const unsigned long array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        const int swap_idx = rand() % array_size;
        swap_(array + i * el_size, array + swap_idx * el_size, el_size);
    }
}
