//
// Created by Fedor Evgr on 13/10/2024.
//

#ifndef LAB3_SRC_C_FILEMANAGER_H
#define LAB3_SRC_C_FILEMANAGER_H

#include "Codes.h"
#include "objects/Vector.h"
#include "objects/Matrix.h"

ErrorCode
readVectorFromFile(RareVector *, char *filename);

ErrorCode
readMatrixFromFile(RareMatrix *, char *filename);

ErrorCode
saveVector(RareVector, char *filename);

ErrorCode
saveMatrix(RareMatrix, char *filename);

#endif //LAB3_SRC_C_FILEMANAGER_H
