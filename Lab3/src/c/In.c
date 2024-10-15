//
// Created by Fedor Evgr on 10/10/2024.
//

#include "In.h"

#include <stdbool.h>
#include <stdio.h>

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
        printf("Position: %lu x %lu\n\n", posBuf->columns, posBuf->rows);

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
rareMatrixFill(RareMatrix *rareMatrix)
{
    printf("Enter matrix info:\n");
    assert(rareMatrix->dims.rows != 0 && rareMatrix->dims.columns);

    bool inputEnd = false;
    InputError code;
    Element newElement = {0};
    double buffer;

    while (!inputEnd)
    {
        code = inputElement(&newElement);

        if (code == INPUT_OK)
        {
            rareMatrixGet((*rareMatrix), newElement.position, &buffer);
            if (buffer == 0.0)
                matrixAddElement(rareMatrix, newElement);
            else
                printf("Element already exists\n");
        }
        else
            inputEnd = true;
    }

    if (rareMatrix->elemAmount == 0)
        return ERROR;
    return OK;
}

InputError
inputParameters(double *value, size_t *index)
{
    InputError code;

    printf("Input value: ");
    do
    {
        code = inputDouble(value);
        if (code == INPUT_E_EMPTY)
            return code;
        if (code)
            printf("Error, try again...\n");
    }
    while (code);

    printf("Input value index: ");
    do
    {
        code = inputUnsigned(index);
        if (code)
            printf("Error, try again...\n");
    }
    while (code);
    return code;
}

ErrorCode
vectorFill(RareVector *rareVector)
{
    printf("Enter vector info:\n");
    double value;
    size_t index;
    for (; rareVector->valueAmount < rareVector->length;)
    {
        if (inputParameters(&value, &index))
        {
            printf("\n\nYou have entered a vector\n");
            break;
        }
        else if (vectorAddElement(rareVector, value, index))
            printf("Could not add, element exists...\n");
    }
    if (rareVector->valueAmount == rareVector->length)
        printf("Vector filled\n");
    return OK;
}

ErrorCode
normalVectorGetElements(BasicVector vector)
{
    InputError code;
    for (size_t i = 0; i < vector.length; ++i)
    {
        printf("Enter element %lu: ", i);
        do
        {
            code = inputDouble(vector.values + i);
            if (code)
                printf("Try again\n");
        }
        while (code);
    }
    return OK;
}

ErrorCode
normalVectorFill(BasicVector vector)
{
    printf("Enter all vector elements\n");

    normalVectorGetElements(vector);

    return OK;
}

void
inputDimensions(size_t *vectorLength, size_t *matrixCols)
{
    InputError userError;
    printf("Enter vector length: ");
    do
    {
        userError = inputUnsigned(vectorLength);
        if (userError != INPUT_OK)
            printf("Input error, retry...\n");
    }
    while (userError != INPUT_OK);
    printf("Enter matrix columns amount: ");
    do
    {
        userError = inputUnsigned(matrixCols);
        if (userError != INPUT_OK)
            printf("Input error, retry...\n");
    }
    while (userError != INPUT_OK);
}

void
inputMultiply(bool *rare)
{
    *rare = true;
    char buffer[MAX_BUFFER_LENGTH + 1];
    bool userInput = false;
    InputError ic;
    printf("Multiply rare matrix: y or n: ");
    do
    {
        ic = inputString(buffer);
        if (ic == INPUT_OK)
        {
            if (buffer[0] == 'y')
                userInput = true;
            else if (buffer[0] == 'n')
                userInput = true, *rare = false;
            else
                printf("Illegal option, retry...\n");
        }
        else
            printf("Input error, retry...\n");
    }
    while (!userInput);
}

double getDouble(void)
{
    double result;
    InputError c;
    do
    {
        c = inputDouble(&result);
        if (c)
            printf("Retry...\n");
    }
    while (c);
    return result;
}

void
normalMatrixFill(BasicMatrix matrix)
{
    printf("Input whole matrix\n");
    for (size_t row = 0; row < matrix.dimensions.rows; ++row)
    {
        for (size_t col = 0; col < matrix.dimensions.columns; ++col)
        {
            printf("Enter element of row %lu, col %lu:", row, col);

            matrix.values[row][col] = getDouble();
        }
    }
}


void
normalMatrixFillByElements(BasicMatrix matrix)
{
    Element elementBuffer = { 0 };
    InputError ie;
    do
    {
        ie = inputElement(&elementBuffer);
        if (INPUT_OK == ie)
        {
            if (elementBuffer.position.columns < matrix.dimensions.columns &&
                elementBuffer.position.rows < matrix.dimensions.rows)
            {
                matrix.values[elementBuffer.position.rows][elementBuffer.position.columns] = elementBuffer.value;
                printf("Element added\n");
            }
            else
                printf("Position out of bounds\n");
        }
        else if (ie == INPUT_E_EMPTY)
            printf("Input done\n");
        else
            printf("Illegal input\n");
    }
    while (ie != INPUT_E_EMPTY);
}

void
normalVectorFillByElements(BasicVector vector)
{
    double value;
    size_t index;
    InputError inErr;

    do
    {
        inErr = inputParameters(&value, &index);
        if (inErr == INPUT_OK)
        {
            vector.values[index] = value;
        }
    }
    while (inErr != INPUT_E_EMPTY);
}

size_t
inputPercentile(void)
{
    printf("Enter fill percentile: ");
    size_t result;
    InputError iErr;
    do
    {
        iErr = inputUnsigned(&result);
        if (result > 100)
        {
            printf("Invalid percentile, try again\n");
            iErr = INPUT_E;
        }
    }
    while (iErr);
    return result;
}

bool
getSaveOption(void)
{
    printf("Save input and result (y|n): ");

    char buffer[MAX_BUFFER_LENGTH + 1] = "";
    InputError ie = inputString(buffer);
    if (ie == INPUT_OK && buffer[0] == 'y')
        return true;
    return false;
}

bool
getResOption(void)
{
    printf("Print in sparse format (y|n): ");

    char buffer[MAX_BUFFER_LENGTH + 1] = "";
    InputError ie = inputString(buffer);
    if (ie == INPUT_OK && buffer[0] == 'y')
        return true;
    return false;
}
