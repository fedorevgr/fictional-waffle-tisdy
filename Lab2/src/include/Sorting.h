#ifndef LAB2_SORTING_H
#define LAB2_SORTING_H

#include "common/ExitCodes.h"
#include "common/Macros.h"

typedef int (*CompFunc)(const void *, const void *);

typedef void (*SortFunc)(void *ptr, unsigned long count, unsigned long size, CompFunc);

void choose_sort(void *ptr, unsigned long count, unsigned long size, CompFunc);
void comb_sort(void *ptr, unsigned long count, unsigned long size, CompFunc);

SortFunc getSort(long pos);

#endif //LAB2_SORTING_H
