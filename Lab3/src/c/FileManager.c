//
// Created by Fedor Evgr on 13/10/2024.
//

#include "FileManager.h"
#include <stdio.h>
#include <assert.h>

ErrorCode
readVector__(RareVector *vector, FILE *file)
{
    fread(&vector->valueAmount, sizeof(size_t), 1, file);
    fread(&vector->length, sizeof(size_t), 1, file);

    double *values = realloc(vector->values, vector->valueAmount * sizeof(double));
    if (!values)
        return ERROR_MEMORY;

    vector->values = values;
    fread(vector->values, sizeof(double), vector->valueAmount, file);

    size_t *indexes = realloc(vector->indexes, vector->valueAmount * sizeof(size_t));
    if (!indexes)
        return ERROR_MEMORY;

    vector->indexes = indexes;
    fread(vector->indexes, vector->valueAmount, sizeof(size_t), file);

    return OK;
}


ErrorCode
readVectorFromFile(RareVector *vector, char *filename)
{
    ErrorCode ec = OK;
    FILE *file = fopen(filename, "rb");
    if (file)
    {
        ec = readVector__(vector, file);
        fclose(file);
    }
    else
        ec = ERROR;
    return ec;
}

ErrorCode
readMatrix__(RareMatrix *matrix, FILE *file)
{
    fread(&matrix->dims, sizeof(Dimensions), 1, file);
    fread(&matrix->elemAmount, sizeof(size_t), 1, file);

    void *buffer = realloc(matrix->colStart, sizeof(size_t) * matrix->dims.columns);
    if (!buffer)
        return ERROR_MEMORY;
    matrix->colStart = buffer;
    fread(matrix->colStart, sizeof(size_t), matrix->dims.columns + 1, file);
    matrix->colStart[matrix->dims.columns] = matrix->dims.columns;

    void *buffer2 = realloc(matrix->values, sizeof(double) * matrix->elemAmount);
    if (!buffer2)
        return ERROR_MEMORY;
    matrix->values = buffer2;
    fread(matrix->values, sizeof(double), matrix->elemAmount, file);

    void *buffer3 = realloc(matrix->rowIndexes, sizeof(size_t) * matrix->elemAmount);
    if (!buffer3)
        return ERROR_MEMORY;
    matrix->rowIndexes = buffer3;
    fread(matrix->rowIndexes, sizeof(size_t), matrix->elemAmount, file);
    return OK;
}

ErrorCode
readMatrixFromFile(RareMatrix *matrix, char *filename)
{
    ErrorCode ec = OK;
    FILE *file = fopen(filename, "rb");
    if (file)
    {
        ec = readMatrix__(matrix, file);
        fclose(file);
    }
    else
        ec =  ERROR;
    return ec;
}

void
saveVector__(RareVector vector, FILE *file)
{
    fwrite(&vector.valueAmount, sizeof(size_t), 1, file);
    fwrite(&vector.length, sizeof(size_t), 1, file);
    fwrite(vector.values, sizeof(double), vector.valueAmount, file);
    fwrite(vector.indexes, sizeof(size_t), vector.valueAmount, file);
}

ErrorCode
saveVector(RareVector vector, char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file)
    {
        saveVector__(vector, file);
        fclose(file);
    }
    else
        return ERROR;
    return OK;
}

void
saveMatrix__(RareMatrix matrix, FILE *file)
{
    fwrite(&matrix.dims, sizeof(Dimensions), 1, file);
    fwrite(&matrix.elemAmount, sizeof(size_t), 1, file);
    fwrite(matrix.colStart, sizeof(size_t), matrix.dims.columns, file);
    fwrite(matrix.values, sizeof(double), matrix.elemAmount, file);
    fwrite(matrix.rowIndexes, sizeof(size_t), matrix.elemAmount, file);
}

ErrorCode
saveMatrix(RareMatrix matrix, char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file)
    {
        saveMatrix__(matrix, file);
        fclose(file);
    }
    else
        return ERROR;
    return OK;
}

#include <time.h>
char *
getFileName(char *buffer, char *start)
{
    time_t current_time = time(NULL);

    struct tm* local_time = localtime(&current_time);

    sprintf(buffer, "%s_%02d_%02d_%02d.bin",
            start,
            local_time->tm_hour,
            local_time->tm_min,
            local_time->tm_sec);
    return buffer;
}
