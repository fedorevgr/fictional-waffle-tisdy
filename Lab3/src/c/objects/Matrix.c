//
// Created by Fedor Evgr on 04/10/2024.
//

#include "objects/Matrix.h"
#include "Input.h"
#include "Arrays.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <assert.h>

InputError
inputPosition(Dimensions *posBuf)
{
    printf("Input column: ");
    InputError ec = inputUnsigned(&posBuf->columns);
    if (ec == INPUT_OK)
    {
        printf("Input row: ");
        ec = inputUnsigned(&posBuf->rows);
    }
    if (ec == INPUT_OK)
        printf("Position: %lu x %lu", posBuf->columns, posBuf->rows);

    return ec;
}

InputError
inputElement(Element *newElementBuffer)
{
    printf("Input element value: ");
    InputError ec = inputDouble(&newElementBuffer->value);
    if (ec == INPUT_OK)
    {
        ec = inputPosition(&newElementBuffer->position);
    }
    return ec;
}

ErrorCode
matrixAddElement(RareMatrix *matrix, const Element element)
{
    RareMatrix bufMatrix = *matrix;
    assert(bufMatrix.values != NULL);
    assert(bufMatrix.colStart != NULL);
    assert(bufMatrix.rowIndexes != NULL);
    assert(bufMatrix.dims.rows != 0 && bufMatrix.dims.columns != 0);
    assert(element.position.rows < bufMatrix.dims.rows && element.position.columns < bufMatrix.dims.columns);

    void *buf = realloc(bufMatrix.values, bufMatrix.elemAmount * sizeof(*bufMatrix.values));
    void *buf2 = realloc(bufMatrix.rowIndexes, bufMatrix.elemAmount * sizeof(*bufMatrix.rowIndexes));
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

    arrayInsert(
        bufMatrix.values, &bufMatrix.elemAmount,
        sizeof(*bufMatrix.values),
        &element.value, rowI
    );
    size_t decoy = bufMatrix.elemAmount;
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
//    assert(matrix.values != NULL);
    assert(matrix.colStart != NULL);
//    assert(matrix.rowIndexes != NULL);

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

ErrorCode
rareMatrixFill(RareMatrix *rareMatrix)
{
    assert(rareMatrix->dims.rows != 0 && rareMatrix->dims.columns);

    bool inputEnd = false;
    InputError code;
    Element newElement = {0};

    while (!inputEnd)
    {
        code = inputElement(&newElement);

        if (code == INPUT_OK)
        {
            break;
        }
        else
            inputEnd = true;
    }
    return OK;
}

#define ARRAY_INIT_SIZE 1

ErrorCode
matrixCreate(RareMatrix *nullMatrix, const Dimensions size)
{
    assert(memcmp(nullMatrix, &(RareMatrix) {0}, sizeof(RareMatrix)) == 0);
    assert(size.rows > 0 && size.columns > 0);

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
    return ERROR;
}

ErrorCode
matrixBasicToRare(RareMatrix *rareMatrix, BasicMatrix )
{

    return OK;
}