#include "File.h"

#include <stdio.h>

#define MAX_ARRAY_SIZE 50000

size_t
readFile(const char *filename, int **elements)
{
    if (elements == nullptr || filename == nullptr)
        return 0;

    *elements = malloc(sizeof(int) * MAX_ARRAY_SIZE);

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
writeFile(const char *filename, const int *elements, size_t length)
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

FileCode
addToFile(const char *filename, const int elem)
{
    FILE *file = fopen(filename, "a");
    if (file)
        return F_ERR;

    fprintf(file, " %d", elem);

    fclose(file);
    return F_OK;
}

FileCode
removeFromFile(const char *filename, const int elem)
{
    int *elements = nullptr;
    size_t length = readFile(filename, &elements);

    if (!elements)
    {
        printf("Error memory\n");
        return F_ERR;
    }
    FileCode ec = F_OK;

    if (length)
    {
        size_t shift = 0;
        for (size_t i = 0; i < length; ++i)
        {
            if (elements[i] == elem)
            {
                shift += 1;
                continue;
            }
            elements[i - shift] = elements[i];
        }
        length -= shift;
        ec = writeFile(filename, elements, length);
    }
    else
        ec = F_ERR;

    if (elements)
        free(elements);

    return ec;
}
