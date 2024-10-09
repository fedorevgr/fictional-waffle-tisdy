//
// Created by Fedor Evgr on 04/10/2024.
//

#ifndef LAB3_SRC_C_MATRIX_H
#define LAB3_SRC_C_MATRIX_H

#include "Codes.h"


typedef struct {
    unsigned long rows;
    unsigned long columns;
} Dimensions;

typedef struct {
    double *values;
    unsigned long *rowIndexes;
    unsigned long *colStart;
    unsigned long elemAmount;
    Dimensions dims;
} RareMatrix;

typedef struct {
    double **values;
    Dimensions dimensions;
} BasicMatrix;

typedef struct
{
    double value;
    Dimensions position;
} Element;

ErrorCode matrixCreate(RareMatrix *nullRareMatrix, Dimensions);
ErrorCode rareMatrixFill(RareMatrix *rareMatrix);
void matrixFree(RareMatrix);

ErrorCode matrixRareToBasic(BasicMatrix *, RareMatrix);
ErrorCode matrixBasicToRare(RareMatrix *, BasicMatrix);

ErrorCode
rareMatrixGet(RareMatrix matrix, Dimensions position, double *result);

ErrorCode
matrixAddElement(RareMatrix *matrix, Element element);


#endif //LAB3_SRC_C_MATRIX_H
