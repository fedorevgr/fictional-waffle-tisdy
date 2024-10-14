//
// Created by Fedor Evgr on 13/10/2024.
//

#include "Stats.h"
#include "objects/Matrix.h"
#include "objects/Vector.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "Meth.h"

#define SIZE_START 10
#define SIZE_STEP  100
#define SIZE_MARK  1000
#define SIZE_STEP2 1000
#define SIZE_LIMIT 10000

#define FILL_START 10
#define FILL_STEP  10
#define FILL_END   100

#define RUNS 3

#define CACHE "cache"


void
runRare(size_t size)
{
    RareVector vector = {0};
    RareMatrix matrix = {0};

    vectorCreate(&vector, size);
    matrixCreate(&matrix, (Dimensions) {.rows = size, .columns = size});


    for (int i = 0; i < RUNS; ++i)
    {
        RareVector result = {0};
        vectorCreate(&result, matrix.dims.columns);

        multiply(matrix, vector, &result);

        vectorFree(result);
    }

    vectorFree(vector);
    matrixFree(matrix);
}
#include <time.h>
#define NANO_SEC(time) (time.tv_sec * 1000000000ULL + time.tv_nsec)


#define SIZE_OF_BASIC(m) (sizeof(Dimensions) + \
                        (m.dimensions.rows * m.dimensions.columns * sizeof(double)))

#define SIZE_OF_RARE(m) (sizeof(Dimensions) + \
                            sizeof(size_t) + ((m.dims.columns + 1) * sizeof(size_t)) + \
                            (sizeof(size_t)) + 2 * (m.elemAmount * sizeof(double)))

void fillObjects(RareVector *vector, RareMatrix *matrix, size_t fill)
{
    BasicVector bv = {0};
    BasicMatrix bm = {0};
    basicVectorCreate(&bv, vector->length);
    basicMatrixCreate(&bm, (Dimensions) {.rows = matrix->dims.rows, .columns = matrix->dims.columns});

    fillRandomBasicVector(bv, fill);
    fillRandomBasicMatrix(&bm, fill);

    matrixBasicToRare(matrix, bm);
    vectorBasicToRare(vector, bv);

    basicMatrixFree(&bm);
    basicVectorFree(&bv);
}

unsigned long measureOneRare(size_t size, size_t fill, size_t *memory)
{
    struct timespec start, end;
    unsigned long timeElapsed = 0;

    RareVector vector = {0};
    RareMatrix matrix = {0};

    vectorCreate(&vector, size);
    matrixCreate(&matrix, (Dimensions) {.rows = size, .columns = size});

    fillObjects(&vector, &matrix, fill);

    for (int i = 0; i < RUNS; ++i)
    {
        RareVector result = {0};
        vectorCreate(&result, matrix.dims.columns);

        clock_gettime(CLOCK_REALTIME, &start);
        multiply(matrix, vector, &result);
        clock_gettime(CLOCK_REALTIME, &end);

        vectorFree(result);
        timeElapsed += NANO_SEC(end) - NANO_SEC(start);
    }

    *memory = SIZE_OF_RARE(matrix);

    vectorFree(vector);
    matrixFree(matrix);


    return timeElapsed / RUNS;
}

unsigned long measureOneBasic(size_t size, size_t fill, size_t *memory)
{
    struct timespec start, end;
    unsigned long timeElapsed = 0;

    BasicVector bv = {0};
    BasicMatrix bm = {0};
    basicVectorCreate(&bv, size);
    basicMatrixCreate(&bm, (Dimensions) {.rows = size, .columns = size});

    fillRandomBasicVector(bv, fill);
    fillRandomBasicMatrix(&bm, fill);

    for (int i = 0; i < RUNS; ++i)
    {
        BasicVector result = { 0 };
        basicVectorCreate(&result, size);

        clock_gettime(CLOCK_REALTIME, &start);
        multiplyBasic(bm, bv, &result);
        clock_gettime(CLOCK_REALTIME, &end);

        basicVectorFree(&result);
        timeElapsed += NANO_SEC(end) - NANO_SEC(start);
    }
    *memory = SIZE_OF_BASIC(bm);

    basicMatrixFree(&bm);
    basicVectorFree(&bv);
    return timeElapsed / RUNS;
}

void
run(size_t size, size_t fill)
{
    char fileName[101] = "";

    sprintf(fileName, CACHE "/%lu/%lu", fill, size);
    size_t size1 = 0;
    size_t size2 = 0;
    FILE *file = fopen(fileName, "w");
    if (file)
    {
        fprintf(file,
                "%lu\n%lu\n%lu\n%lu\n",
                measureOneRare(size, fill, &size1),
                measureOneBasic(size, fill, &size2),
                size1,
                size2);
        fclose(file);
    }
}

ErrorCode createSourceDir(void)
{
    if (mkdir(CACHE, 0755))
    {
        if (rmdir(CACHE))
            return ERROR;
        if (mkdir(CACHE, 0755))
            return ERROR;
    }
    return OK;
}


ErrorCode
runStats(void)
{
    printf("\n");
    ErrorCode ec = createSourceDir();
    if (ec)
        return ec;

    char buffer[51] = "";

    for (size_t percentile = FILL_START; percentile <= FILL_END; percentile += FILL_STEP)
    {
        printf("Stats: %lu%%/%d\n", percentile, FILL_END);
        sprintf(buffer, CACHE "/%lu", percentile);
        if (mkdir(buffer, 0755))
            continue;

        for (size_t objSize = SIZE_START; objSize <= SIZE_MARK; objSize += SIZE_STEP)
        {
            printf("Stats: %lu%%/%d -- %lu/%d\n", percentile, FILL_END, objSize, SIZE_LIMIT);
            run(objSize, percentile);
        }
        for (size_t objSize = SIZE_MARK; objSize <= SIZE_LIMIT; objSize += SIZE_STEP2)
        {
            printf("Stats: %lu%%/%d -- %lu/%d\n", percentile, FILL_END, objSize, SIZE_LIMIT);
            run(objSize, percentile);
        }
    }
    printf("\n");
    return OK;
}
