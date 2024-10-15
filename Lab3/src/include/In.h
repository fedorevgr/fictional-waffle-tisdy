//
// Created by Fedor Evgr on 10/10/2024.
//

#ifndef LAB3_SRC_C_IN_H
#define LAB3_SRC_C_IN_H

#include "simple/PrimitiveInput.h"
#include "objects/Matrix.h"
#include "objects/Vector.h"
#include "Codes.h"
#include <stdbool.h>

ErrorCode
rareMatrixFill(RareMatrix *rareMatrix);

ErrorCode
vectorFill(RareVector *rareVector);

ErrorCode
normalVectorFill(BasicVector vector);

void
inputDimensions(size_t *vectorLength, size_t *matrixCols);

void
inputMultiply(bool *rare);

void
normalMatrixFill(BasicMatrix matrix);

void
normalMatrixFillByElements(BasicMatrix matrix);

void
normalVectorFillByElements(BasicVector vector);

size_t
inputPercentile(void);

bool
getSaveOption(void);

bool
getResOption(void);

#endif //LAB3_SRC_C_IN_H
