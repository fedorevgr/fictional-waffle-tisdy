//
// Created by Fedor Evgr on 13/10/2024.
//

#include "FileManager.h"
#include <stdio.h>
#include <assert.h>

ErrorCode
readVector__(RareVector *vector, FILE *file)
{
    assert(vector->values == NULL);
    assert(vector->indexes == NULL);

    fread(&vector->valueAmount, sizeof(size_t), 1, file);
    fread(&vector->length, sizeof(size_t), 1, file);

    double *values = calloc(vector->valueAmount, sizeof(double));
    if (!values)
        return ERROR_MEMORY;

    vector->values = values;
    fread(vector->values, sizeof(double), vector->valueAmount, file);

    size_t *indexes = calloc(vector->valueAmount, sizeof(size_t));
    if (!indexes)
    {
        return ERROR_MEMORY;
    }
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
    assert(matrix->rowIndexes == NULL);
    assert(matrix->values == NULL);
    assert(matrix->colStart == NULL);

    fread(&matrix->dims, sizeof(Dimensions), 1, file);
    fread(&matrix->elemAmount, sizeof(size_t), 1, file);

    matrix->colStart = calloc(sizeof(size_t), matrix->dims.columns);
    if (!matrix->colStart)
        return ERROR_MEMORY;
    fread(matrix->colStart, sizeof(size_t), matrix->dims.columns, file);

    matrix->values = calloc(sizeof(double), matrix->elemAmount);
    if (!matrix->values)
        return ERROR_MEMORY;
    fread(matrix->values, sizeof(double), matrix->elemAmount, file);

    matrix->rowIndexes = calloc(sizeof(size_t), matrix->elemAmount);
    if (!matrix->rowIndexes)
        return ERROR_MEMORY;
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
    FILE *file = fopen(filename, "wb+");
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
    FILE *file = fopen(filename, "wb+");
    if (file)
    {
        saveMatrix__(matrix, file);
        fclose(file);
    }
    else
        return ERROR;
    return OK;
}
