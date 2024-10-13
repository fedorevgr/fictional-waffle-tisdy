#include "objects/Vector.h"
#include <stdlib.h>
#include "objects/Matrix.h"
#include "Meth.h"
#include "Output.h"


int main(void)
{
    BasicMatrix basicMatrix = { 0 };
    Dimensions dimensions = {.rows = 3, .columns = 3};
    basicMatrixCreate(&basicMatrix, dimensions);

    basicMatrix.values[0][2] = 1;
    basicMatrix.values[1][0] = 1;
    basicMatrix.values[1][1] = 1;
    basicMatrix.values[2][2] = 1;

    printNormalMatrix(basicMatrix);

    RareMatrix rareMatrix = { 0 };
    matrixCreate(&rareMatrix, dimensions);

    matrixBasicToRare(&rareMatrix, basicMatrix);

    printRareMatrix(rareMatrix);

    matrixFree(rareMatrix);
    basicMatrixFree(&basicMatrix);

    return OK;
}

