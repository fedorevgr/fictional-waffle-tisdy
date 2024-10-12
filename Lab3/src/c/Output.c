//
// Created by Fedor Evgr on 10/10/2024.
//

#include "Output.h"

#include <stdio.h>
#define PRINT_AMOUNT    30

void
printRareMatrixInZip(RareMatrix matrix)
{
    for (size_t valI = 0; valI < matrix.elemAmount; ++valI)
        printf("%lf ", matrix.values[valI]);
    printf("\n");

    for (size_t valI = 0; valI < matrix.elemAmount; ++valI)
        printf("%lu ", matrix.rowIndexes[valI]);
    printf("\n");

    for (size_t colI = 0; colI < matrix.dims.columns; ++colI)
        printf("%lu ", matrix.colStart[colI]);
    printf("\n");
}

void
printRareMatrixSimple(RareMatrix matrix)
{
    double result;
    for (size_t row = 0; row < matrix.dims.rows; row++)
    {
        for (size_t col = 0; col < matrix.dims.columns; col++)
        {
            if (OK == rareMatrixGet(matrix, (Dimensions) {.rows = row, .columns = col}, &result))
                printf("%lf ", result);
        }
        printf("\n");
    }
    printf("\n");
}

void
printRareMatrix(RareMatrix matrix)
{
    printf("Matrix\n");
    if (matrix.dims.columns > PRINT_AMOUNT || matrix.dims.rows > PRINT_AMOUNT)
        printRareMatrixInZip(matrix);
    else
        printRareMatrixSimple(matrix);
}

void
printNormalMatrix(BasicMatrix matrix)
{
    for (size_t row = 0; row < matrix.dimensions.rows; row++)
    {
        for (size_t col = 0; col < matrix.dimensions.columns; col++)
        {
            printf("%lf ", matrix.values[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

void
printRareVector(RareVector vector)
{
    printf("Vector\n");
    for (size_t col = 0; col < vector.length; col++)
    {
        printf("%lf ", rareVectorGet(vector, col));
    }
    printf("\n");
}

void
printNormalVector(BasicVector vector)
{
    for (size_t i = 0; i < vector.length; ++i)
        printf("%lf ", vector.values[i]);
    printf("\n");
}


