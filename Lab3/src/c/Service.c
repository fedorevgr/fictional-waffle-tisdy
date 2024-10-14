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
#include "FileManager.h"
#include "Stats.h"
#include <time.h>
#define NANO_SEC(time) (time.tv_sec * 1000000000ULL + time.tv_nsec)

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
           " - from file: R\n"
           "Option -> ");
    char buffer[MAX_BUFFER_LENGTH + 1] = "";

    InputError iErr;
    do
    {
        iErr = inputString(buffer);
        if (iErr == INPUT_OK && strpbrk(buffer, "ENAR") != buffer)
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
        case 'R':option = READ;
            break;
    }
    return option;
}

void
serviceStats(void)
{
    runStats();
}

ErrorCode
serviceMultiplyRare(void)
{
    ErrorCode code = 0;
    Mode inputMode = inputModeOption();
    bool save = getSaveOption();

    RareVector vector = {0};
    RareMatrix matrix = {0};

    size_t vectorLength = 0;
    size_t matrixColumns = 0;

    if (inputMode != READ)
    {
        inputDimensions(&vectorLength, &matrixColumns);
        printf(GAP);

        code += vectorCreate(&vector, vectorLength);
        code += matrixCreate(&matrix, (Dimensions) {.rows = vectorLength, .columns = matrixColumns});
    }

    if (!code)
    {
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
        {
            char vectorFileName[MAX_BUFFER_LENGTH + 1] = "";

            printf("Input vector file name: ");
            inputString(vectorFileName);

            code += readVectorFromFile(&vector, vectorFileName);

            if (!code)
            {
                char matrixFileName[MAX_BUFFER_LENGTH + 1] = "";

                printf("Input matrix file name: ");
                inputString(matrixFileName);

                code += readMatrixFromFile(&matrix, matrixFileName);
                if (code)
                    printf("Could not read the file\n");
                else if (vector.length != matrix.dims.rows)
                {
                    printf("Incompatible objects dimensions\n");
                    code = ERROR;
                }
            }
            else
                printf("Could not read the file\n");
        }
        else
            assert(0); // option should not be here
    }

    RareVector vectorResult = {0};
    code += vectorCreate(&vectorResult, matrix.dims.columns);

    if (code)
    {
        printf("Error memory\n");
        code = ERROR;
    }
    else
    {
        printf(GAP);
        printRareVector(vector);
        printf("*\n");
        printRareMatrix(matrix);

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);
        multiply(matrix, vector, &vectorResult);
        clock_gettime(CLOCK_REALTIME, &end);

        printRareVector(vectorResult);
        printf("Time: %llu\n",   NANO_SEC(end) -NANO_SEC(start));
    }

    if (!code && save)
    {
        if (inputMode != READ)
        {
            char vectorFileName[MAX_BUFFER_LENGTH + 1] = "";
            char matrixFileName[MAX_BUFFER_LENGTH + 1] = "";

            saveVector(vector, getFileName(vectorFileName, "InVector"));
            saveMatrix(matrix, getFileName(matrixFileName, "InMatrix"));
        }

        char resultFileName[MAX_BUFFER_LENGTH * 3 + 1] = "";
        saveVector(vectorResult, getFileName(resultFileName, "ResVector"));
    }

    vectorFree(vector);
    matrixFree(matrix);
    vectorFree(vectorResult);

    return code;
}

ErrorCode
serviceMultiplyBasic(void)
{
    Mode inputMode = inputModeOption();

    if (inputMode == READ)
    {
        printf("File operations not supported for normal representation\n");
        return ERROR;
    }

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
        else
            assert(0); // option should not be here
    }

    if (code)
    {
        printf("Error memory\n");
        code = ERROR;
    }
    else
    {
        printf(GAP);
        printNormalVector(vector);
        printf("*\n");
        printNormalMatrix(matrix);
        printf("=\n");

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);
        multiplyBasic(matrix, vector, &vectorResult);
        clock_gettime(CLOCK_REALTIME, &end);

        printNormalVector(vectorResult);
        printf("Time: %llu\n",   NANO_SEC(end) -NANO_SEC(start));
    }

    basicVectorFree(&vector);
    basicMatrixFree(&matrix);
    basicVectorFree(&vectorResult);

    return code;
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
