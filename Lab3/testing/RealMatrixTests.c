//
// Created by Fedor Evgr on 07/10/2024.
//
#include "objects/Matrix.h"

#include <check.h>

#include <stdlib.h>
#include <stdio.h>

START_TEST(matr_get)
{
    RareMatrix matrix = {
        .values = (double[]) {1.},
        .rowIndexes = (size_t[]) {1},
        .dims = { .rows = 3, .columns = 4 },
        .colStart = (size_t[]) {0, 0, 1, 1, 1}
    };

    double result;
    ErrorCode res = rareMatrixGet(matrix, (Dimensions) {.rows = 1, .columns = 1}, &result);

    ck_assert_double_eq(result, 1.);
    ck_assert(res == OK);
}
END_TEST

START_TEST(matr_create)
{
    Dimensions matrixSize = {.rows = 3, .columns = 4};
    RareMatrix rareMatrix = { 0 };
    ErrorCode code = matrixCreate(&rareMatrix, matrixSize);

    Element element = {
        .value = 1,
        .position = {.rows = 1, .columns = 1}
    };

    ck_assert_int_eq(code, OK);

    matrixAddElement(&rareMatrix, element);

    RareMatrix rareMatrixResult = {
        .values = (double[]) {1.},
        .rowIndexes = (size_t[]) {1},
        .dims = { .rows = 3, .columns = 4 },
        .colStart = (size_t[]) {0, 0, 1, 1, 1},
        .elemAmount = 1
    };

    ck_assert_int_eq(rareMatrix.elemAmount, rareMatrixResult.elemAmount);
    ck_assert_double_eq(rareMatrix.values[0], rareMatrixResult.values[0]);
    ck_assert_int_eq(rareMatrix.rowIndexes[0], rareMatrixResult.rowIndexes[0]);
    ck_assert_mem_eq(rareMatrix.colStart, rareMatrixResult.colStart, sizeof(size_t) * rareMatrixResult.dims.columns);
    ck_assert_int_eq(rareMatrix.colStart[rareMatrixResult.dims.columns], rareMatrixResult.colStart[rareMatrixResult.dims.columns]);

    RareMatrix rareMatrixTwoElem = {
        .values = (double[]) {1., 2.},
        .rowIndexes = (size_t[]) {1, 2},
        .dims = { .rows = 3, .columns = 4 },
        .colStart = (size_t[]) {0, 0, 1, 2, 2},
        .elemAmount = 2
    };

    matrixAddElement(
        &rareMatrix,
        (Element) {.value = 2, .position = {.rows = 2, .columns = 2}}
        );

    ck_assert_int_eq(rareMatrix.elemAmount, rareMatrixTwoElem.elemAmount);
    ck_assert_double_eq(rareMatrix.values[0], rareMatrixTwoElem.values[0]);
    ck_assert_int_eq(rareMatrix.rowIndexes[0], rareMatrixTwoElem.rowIndexes[0]);
    ck_assert_mem_eq(rareMatrix.colStart, rareMatrixTwoElem.colStart, sizeof(size_t) * rareMatrixTwoElem.dims.columns);
    ck_assert_int_eq(rareMatrix.colStart[rareMatrixTwoElem.dims.columns], rareMatrixTwoElem.colStart[rareMatrixTwoElem.dims.columns]);

    matrixFree(rareMatrix);
}
END_TEST


Suite *posSuite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Matrix");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, matr_create);
    tcase_add_test(tc_core, matr_get);
    suite_add_tcase(s, tc_core);

    return s;
}

