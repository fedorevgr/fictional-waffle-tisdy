//
// Created by Fedor Evgr on 10/10/2024.
//

#ifndef LAB3_SRC_OUTPUT_H
#define LAB3_SRC_OUTPUT_H

#include "objects/Matrix.h"
#include "objects/Vector.h"

#include <stdbool.h>

void
printRareMatrix(RareMatrix matrix, bool);

void
printNormalMatrix(BasicMatrix matrix);

void
printNormalVector(BasicVector);

void
printRareVector(RareVector vector, bool);

#endif //LAB3_SRC_OUTPUT_H
