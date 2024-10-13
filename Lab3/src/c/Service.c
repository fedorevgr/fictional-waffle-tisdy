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
#include <string.h>

// todo print result before gap

#define GAP "\n\n\n\n\n\n\n"

typedef enum
{
    WHOLE,
    PARTIAL,
    AUTO,
    READ
} Mode;

Mode
inputModeOption(void)
{
    printf("Input fill mode:\n"
           " - fill entire: E\n"
           " - fill only nonnull: N\n"
           " - auto fill: A\n"
           " - from file: F\n"
           "Option -> ");
    char buffer[MAX_BUFFER_LENGTH + 1] = "";

    InputError iErr;
    do
    {
        iErr = inputString(buffer);
        if (iErr == INPUT_OK && strpbrk(buffer, "ENAF") != buffer)
            iErr = INPUT_E;
    }
    while (iErr != INPUT_OK);

    Mode option;
    switch (buffer[0])
    {
        case 'E':option = WHOLE;
            break;
        case 'N':option = PARTIAL;
            break;
        case 'A':option = AUTO;
            break;
        case 'F':option = READ;
            break;
    }
    return option;
}

void
serviceStats(void) {}

ErrorCode
serviceMultiplyRare(void)
{
    ErrorCode code = 0;
    Mode inputMode = inputModeOption();

    RareVector vector = {0};
    RareMatrix matrix = {0};
    RareVector vectorResult = {0};

    size_t vectorLength = 0;
    size_t matrixColumns = 0;

    inputDimensions(&vectorLength, &matrixColumns);
    printf(GAP);

    code += vectorCreate(&vector, vectorLength);
    code += matrixCreate(&matrix, (Dimensions) {.rows = vectorLength, .columns = matrixColumns});
    code += vectorCreate(&vectorResult, matrixColumns);

    if (code)
    {
        printf("Out of memory\n");
        return ERROR_MEMORY;
    }

    if (inputMode == WHOLE || inputMode == AUTO)
    {
        BasicVector bv = {0};
        BasicMatrix bm = {0};
        basicVectorCreate(&bv, vectorLength);
        basicMatrixCreate(&bm, (Dimensions) {.rows = vectorLength, .columns = matrixColumns});

        if (inputMode == WHOLE)
        {
            normalVectorFill(bv);
            normalMatrixFill(bm);
        }
        else
        {
            size_t percentile = inputPercentile();
            fillRandomBasicVector(bv, percentile);
            fillRandomBasicMatrix(&bm, percentile);
        }

        matrixBasicToRare(&matrix, bm);
        vectorBasicToRare(&vector, bv);

        basicMatrixFree(&bm);
        basicVectorFree(&bv);
    }
    else if (inputMode == PARTIAL)
    {
        vectorFill(&vector);
        rareMatrixFill(&matrix);
    }
    else if (inputMode == READ)
        assert(0); // not implemented
    else
        assert(0); // option should not be here

    printf(GAP);
    printRareVector(vector);
    printf("*\n");
    printRareMatrix(matrix);

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
    Mode inputMode = inputModeOption();

    BasicVector vector = {0};
    BasicMatrix matrix = {0};
    BasicVector vectorResult = {0};

    size_t vectorLength = 0;
    size_t matrixColumns = 0;

    inputDimensions(&vectorLength, &matrixColumns);
    printf(GAP);

    ErrorCode code = OK;
    code += basicVectorCreate(&vector, vectorLength);
    code += basicMatrixCreate(&matrix, (Dimensions) {.rows = vectorLength, .columns = matrixColumns});
    code += basicVectorCreate(&vectorResult, matrixColumns);

    if (!code)
    {
        if (inputMode == WHOLE)
        {
            normalVectorFill(vector);
            normalMatrixFill(matrix);
        }
        else if (inputMode == PARTIAL)
        {
            normalVectorFillByElements(vector);
            normalMatrixFillByElements(matrix);
        }
        else if (inputMode == AUTO)
        {
            size_t percentile = inputPercentile();
            fillRandomBasicVector(vector, percentile);
            fillRandomBasicMatrix(&matrix, percentile);
        }
        else if (inputMode == READ)
            assert(0); // not implemented
        else
            assert(0); // option should not be here
    }
    printf(GAP);
    printNormalVector(vector);
    printf("*\n");
    printNormalMatrix(matrix);
    printf("=\n");

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
