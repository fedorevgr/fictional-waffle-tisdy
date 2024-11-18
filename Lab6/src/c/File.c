#include "File.h"

#include <stdio.h>

size_t
readFile(const char *filename, Elem **elements)
{
    if (elements == nullptr || filename == nullptr)
        return 0;

    *elements = malloc(sizeof(Elem) * MAX_ARRAY_SIZE);

    if (*elements == nullptr)
        return 0;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        free(*elements);
        *elements = nullptr;
        return 0;
    }
    int i = 0;
    for (; i < MAX_ARRAY_SIZE && fscanf(file, "%d", *elements + i) == 1; ++i);

    fclose(file);
    return i;
}

FileCode
writeFile(const char *filename, const Elem *elements, size_t length)
{
    if (length == 0 || elements == nullptr)
        return F_ERR;

    FILE *file = fopen(filename, "w");
    if (!file)
        return F_ERR;

    for (size_t i = 0; i < length; ++i)
        fprintf(file, "%d\n", elements[i]);

    fclose(file);
    return F_OK;
}
