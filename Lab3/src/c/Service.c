//
// Created by Fedor Evgr on 10/10/2024.
//

#include "Service.h"
#include <stdbool.h>
#include <stdio.h>
#include "In.h"
#include "objects/Matrix.h"
#include "objects/Vector.h"
#include "Meth.h"
#include "Output.h"

// todo print result before gap

void
serviceStats(void)
{}


ErrorCode
serviceMultiplyRare(void)
{
    ErrorCode code = 0;
    bool simpleInput = inputSimple();

    RareVector vector = { 0 };
    RareMatrix matrix = { 0 };
    RareVector vectorResult = { 0 };

    size_t vectorLength = 0;
    size_t matrixColumns = 0;

    inputDimensions(&vectorLength, &matrixColumns);

    code += vectorCreate(&vector, vectorLength);
    code += matrixCreate(&matrix, (Dimensions) {.rows = vectorLength, .columns = matrixColumns});
    code += vectorCreate(&vectorResult, matrixColumns);

    if (code)
    {
        printf("Out of memory\n");
        return ERROR_MEMORY;
    }

    if (simpleInput)
    {
        BasicVector bv = { 0 };
        BasicMatrix bm = { 0 };
        basicVectorCreate(&bv, vectorLength);
        basicMatrixCreate(&bm, (Dimensions) {.rows = vectorLength, .columns = matrixColumns});

        normalVectorFill(bv);
        normalMatrixFill(bm);

        matrixBasicToRare(&matrix, bm);
        vectorBasicToRare(&vector, bv);

        basicMatrixFree(&bm);
        basicVectorFree(&bv);
    }
    else
    {
        vectorFill(&vector);
        rareMatrixFill(&matrix);
    }

    multiply(matrix, vector, &vectorResult);
    printRareVector(vectorResult);


    vectorFree(vector);
    matrixFree(matrix);
    vectorFree(vectorResult);

    return code;
}

ErrorCode
serviceMultiplyBasic(void)
{
    bool simpleInput = inputSimple();

    BasicVector vector = { 0 };
    BasicMatrix matrix = { 0 };
    BasicVector vectorResult = { 0 };

    size_t vectorLength = 0;
    size_t matrixColumns = 0;

    inputDimensions(&vectorLength, &matrixColumns);

    ErrorCode code = OK;
    code += basicVectorCreate(&vector, vectorLength);
    code += basicMatrixCreate(&matrix, (Dimensions) {.rows = vectorLength, .columns = matrixColumns});
    code += basicVectorCreate(&vectorResult, matrixColumns);

    if (!code)
    {
        if (simpleInput)
        {
            normalVectorFill(vector);
            normalMatrixFill(matrix);
        }
        else
        {
            normalVectorFillByElements(vector);
            normalMatrixFillByElements(matrix);
        }
    }

    if (code)
    {
        printf("Error memory\n");
        return ERROR;
    }
    else
        multiplyBasic(matrix, vector, &vectorResult);

    printNormalVector(vectorResult);

    basicVectorFree(&vector);
    basicMatrixFree(&matrix);
    basicVectorFree(&vectorResult);

    return OK;
}

void
serviceMultiply(void)
{
    bool rare;
    inputMultiply(&rare);

    ErrorCode code;
    if (rare)
        code = serviceMultiplyRare();
    else
        code = serviceMultiplyBasic();

    if (code == ERROR)
        printf("Error, retry...\n");
    else if (code == ERROR_MEMORY)
        printf("Error, out of memory\n");
}
