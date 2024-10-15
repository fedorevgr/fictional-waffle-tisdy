//
// Created by Fedor Evgr on 10/10/2024.
//

#include "Output.h"

#include <stdio.h>
#define PRINT_AMOUNT    30

void
printRareMatrixInZip(RareMatrix matrix)
{
    printf("Spare representation\n");
    printf("V: ");
    for (size_t valI = 0; valI < matrix.elemAmount; ++valI)
        printf("%6G ", matrix.values[valI]);
    printf("\nR: ");

    for (size_t valI = 0; valI < matrix.elemAmount; ++valI)
        printf("%6lu ", matrix.rowIndexes[valI]);
    printf("\nC: ");

    for (size_t colI = 0; colI < matrix.dims.columns; ++colI)
        printf("%6lu ", matrix.colStart[colI]);
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
                printf("%6G ", result);
        }
        printf("\n");
    }
    printf("\n");
}

void
printRareMatrix(RareMatrix matrix, bool sparse)
{
    printf("Matrix\n");
    if (sparse || matrix.dims.columns > PRINT_AMOUNT || matrix.dims.rows > PRINT_AMOUNT)
        printRareMatrixInZip(matrix);
    else
        printRareMatrixSimple(matrix);
}

void
printNormalMatrix(BasicMatrix matrix)
{
    printf("Matrix\n");
    if (matrix.dimensions.rows <= 30 && matrix.dimensions.columns <= 30)
    {
        for (size_t row = 0; row < matrix.dimensions.rows; row++)
        {
            for (size_t col = 0; col < matrix.dimensions.columns; col++)
            {
                printf("%6G ", matrix.values[row][col]);
            }
            printf("\n");
        }
    }
    else
    {
        for (size_t row = 0; row < matrix.dimensions.rows; row++)
        {
            for (size_t col = 0; col < matrix.dimensions.columns; col++)
            {
                if (matrix.values[row][col] != 0.0)
                    printf("%6G [%lu, %lu]\n", matrix.values[row][col], row, col);
            }
        }
    }
    printf("\n");
}

void
printRareVector(RareVector vector, bool sparse)
{
    printf("Vector\n");
    if (vector.length <= PRINT_AMOUNT && !sparse)
    {
        printf("Indx: ");
        for (size_t I = 0; I < vector.length; ++I)
        {
            printf("%6lu\t", I);
        }
        printf("\nVals: ");
        for (size_t col = 0; col < vector.length; col++)
        {
            printf("%6G\t", rareVectorGet(vector, col));
        }
        printf("\n");
    }
    else
    {
        printf("Indx: ");
        for (size_t I = 0; I < vector.valueAmount; ++I)
            printf("%6lu\t", vector.indexes[I]);
        printf("\nVals: ");
        for (size_t I = 0; I < vector.valueAmount; ++I)
            printf("%6G\t", vector.values[I]);
        printf("\n");
    }
}

void
printNormalVector(BasicVector vector)
{
    printf("Vector\n");

    if (vector.length <= 30)
    {
        for (size_t i = 0; i < vector.length; ++i)
            printf("%6lu\t", i);
        printf("\n");

        for (size_t i = 0; i < vector.length; ++i)
            printf("%6G\t", vector.values[i]);
        printf("\n");
    }
    else
    {
        for (size_t i = 0; i < vector.length; ++i)
            if (vector.values[i] != 0.0)
                printf("%6lu\t", i);
        printf("\n");

        for (size_t i = 0; i < vector.length; ++i)
            if (vector.values[i] != 0.0)
                printf("%6G\t", vector.values[i]);
        printf("\n");
    }
}


