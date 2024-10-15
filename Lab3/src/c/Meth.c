//
// Created by Fedor Evgr on 08/10/2024.
//

#include "Meth.h"
#include <stdlib.h>


ErrorCode
multiply(const RareMatrix matrix, const RareVector vector, RareVector *result)
{
    if (vector.length != matrix.dims.rows || matrix.dims.columns != result->length)
        return ERROR;

    double sum;
    size_t rowStartI, rowEndI;
    size_t vectorLastI;
    for (size_t colI = 0; colI < matrix.dims.columns; ++colI)
    {
        rowStartI = matrix.colStart[colI];
        rowEndI = matrix.colStart[colI + 1];

        if (rowEndI - rowStartI != 0)
        {
            sum = 0;
            vectorLastI = matrix.rowIndexes[rowStartI];
            for (; rowStartI < rowEndI; rowStartI++)
            {
                sum += rareVectorGet(
                    vector,
                    matrix.rowIndexes[rowStartI]
                ) * matrix.values[rowStartI];
            }
            if (sum)
                vectorAddElement(result, sum, colI);
        }
    }
    return OK;
}

ErrorCode
multiplyBasic(BasicMatrix matrix, BasicVector vector, BasicVector *result)
{
    double sum;
    for (size_t col = 0; col < matrix.dimensions.columns; ++col)
    {
        sum = 0;

        for (size_t row = 0; row < matrix.dimensions.rows; ++row)
        {
            sum += matrix.values[row][col] * vector.values[row];
        }

        result->values[col] = sum;
    }
    return OK;
}
