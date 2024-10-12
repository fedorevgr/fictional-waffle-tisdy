//
// Created by Fedor Evgr on 04/10/2024.
//

#include "objects/Matrix.h"
#include "simple/PrimitiveInput.h"
#include "Arrays.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

ErrorCode
matrixAddElement(RareMatrix *matrix, const Element element)
{
    RareMatrix bufMatrix = *matrix;
    assert(bufMatrix.values != NULL);
    assert(bufMatrix.colStart != NULL);
    assert(bufMatrix.rowIndexes != NULL);

    void *buf = realloc(bufMatrix.values, (bufMatrix.elemAmount + 1) * sizeof(*bufMatrix.values));
    void *buf2 = realloc(bufMatrix.rowIndexes, (bufMatrix.elemAmount + 1) * sizeof(*bufMatrix.rowIndexes));
    if (buf && buf2)
        bufMatrix.values = buf, bufMatrix.rowIndexes = buf2;
    else
        return ERROR_MEMORY; // Couldn't add

    size_t i = bufMatrix.dims.columns - 1;
    for (; element.position.columns != i; i--)
    {
        bufMatrix.colStart[i] += 1;
    }
    size_t rowI = bufMatrix.colStart[i];
    for (; element.position.rows < bufMatrix.rowIndexes[rowI]; rowI++);

    size_t decoy = bufMatrix.elemAmount;
    arrayInsert(
        bufMatrix.values, &bufMatrix.elemAmount,
        sizeof(*bufMatrix.values),
        &element.value, rowI
    );

    arrayInsert(
        bufMatrix.rowIndexes, &decoy,
        sizeof(*bufMatrix.rowIndexes),
        &element.position.rows, rowI
    );

    bufMatrix.colStart[bufMatrix.dims.columns] = bufMatrix.elemAmount;

    *matrix = bufMatrix;
    return OK;
}

ErrorCode
rareMatrixGet(const RareMatrix matrix, const Dimensions position, double *result)
{
    assert(matrix.colStart != NULL);
    assert(matrix.dims.columns > position.columns && matrix.dims.rows > position.rows);

    *result = 0;

    size_t colStartIndex = matrix.colStart[position.columns];
    size_t colElementAmount = matrix.colStart[position.columns + 1] - colStartIndex;

    size_t found;
    ErrorCode findCode = arrayFind(
        matrix.rowIndexes + colStartIndex, colElementAmount,
        sizeof(&matrix.rowIndexes),
        &position.rows, &found
    );

    if (findCode == OK)
        *result = matrix.values[found];

    return OK;
}

#define ARRAY_INIT_SIZE 1

ErrorCode
matrixCreate(RareMatrix *nullMatrix, const Dimensions size)
{
    assert(memcmp(nullMatrix, &(RareMatrix) {0}, sizeof(RareMatrix)) == 0);

    nullMatrix->values = calloc(ARRAY_INIT_SIZE, sizeof(double));
    nullMatrix->rowIndexes = calloc(ARRAY_INIT_SIZE, sizeof(size_t));

    nullMatrix->dims = size;
    nullMatrix->elemAmount = 0;
    nullMatrix->colStart = calloc(size.columns + 1, sizeof(nullMatrix->colStart));
    if (nullMatrix->colStart == NULL)
        return ERROR;

    for (size_t i = 0; i <= size.columns; i++)
        nullMatrix->colStart[i] = nullMatrix->elemAmount;

    return OK;
}

void
matrixFree(RareMatrix matrix)
{
    free(matrix.values);
    free(matrix.rowIndexes);
    free(matrix.colStart);
}

ErrorCode
matrixRareToBasic(BasicMatrix *basicMatrix, RareMatrix rareMatrix)
{
    return OK;
}

ErrorCode
matrixBasicToRare(RareMatrix *rareMatrix, BasicMatrix m)
{
    assert(rareMatrix->dims.columns == m.dimensions.columns);
    assert(rareMatrix->dims.rows == m.dimensions.rows);

    for (size_t row = 0; row < m.dimensions.rows; ++row)
    {
        for (size_t col = 0; col < m.dimensions.columns; ++col)
        {
            matrixAddElement(rareMatrix,
                             (Element) {
                                 .value = m.values[row][col],
                                 .position =
                                 (Dimensions) {
                                     .rows = row,
                                     .columns = col
                                 }
                             });
        }
    }
    return OK;
}

ErrorCode
basicMatrixCreate(BasicMatrix *matrix, Dimensions dims)
{
    matrix->dimensions = dims;
    matrix->values = calloc(dims.rows, sizeof(double *));
    if (!matrix->values)
        return ERROR_MEMORY;

    for (size_t i = 0; i < dims.columns; ++i)
    {
        matrix->values[i] = calloc(dims.columns, sizeof(double));
        if (!matrix->values[i])
        {
            basicMatrixFree(matrix);
            return ERROR_MEMORY;
        }
    }
    return OK;
}

void
basicMatrixFree(BasicMatrix *matrix)
{
    if (matrix->values)
    {
        for (size_t i = 0; i < matrix->dimensions.rows; ++i)
            free(matrix->values[i]);
        free(matrix->values);
    }
    matrix->dimensions = (Dimensions) {0};
}
