#include "objects/Vector.h"
#include <stdlib.h>
#include "objects/Matrix.h"
#include "Meth.h"
#include "Output.h"


int main(void)
{
    RareVector vector = { 0 };
    vectorCreate(&vector, 5);
    vectorAddElement(&vector, 1.1, 0);
    vectorAddElement(&vector, 4, 4);
    vectorAddElement(&vector, 2, 2);
    vectorAddElement(&vector, 1.5, 1);
    printRareVector(vector);

    RareMatrix matrix = {0};

    matrixCreate(&matrix, (Dimensions) {.rows = 5, .columns = 5});
    for (int i = 0; i < matrix.dims.rows; ++i)
    {
        matrixAddElement(
            &matrix,
            (Element) {
                .value = 1,
                .position = {
                    .rows = i,
                    .columns = i
                }
            });

    }
    matrixAddElement(&matrix, (Element) {
        .value = 1,
        .position = {
            .rows = 0,
            .columns = 4
        }
        });
    printRareMatrix(matrix);

    RareVector result = { 0 };
    vectorCreate(&result, 5);

    multiply(matrix, vector, &result);
    printRareVector(result);

    return OK;
}

