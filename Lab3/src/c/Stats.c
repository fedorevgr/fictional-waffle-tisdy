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

#define RUNS 20

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

typedef struct
{
    size_t timeRare;
    size_t timeBasic;
    size_t memRare;
    size_t memBasic;
} Data;

void
run(size_t size, size_t fill, Data *d)
{
    size_t size1 = 0;
    size_t size2 = 0;

    d->timeRare = measureOneRare(size, fill, &size1) / 1000;
    d->timeBasic = measureOneBasic(size, fill, &size2) / 1000;
    d->memRare = size1;
    d->memBasic = size2;
}


#define SIZE_START 50
#define SIZE_STEP  225
#define SIZE_LIMIT 510

#define FILL_START 10
#define FILL_STEP  20
#define FILL_END   100

ErrorCode
runStats(void)
{
    printf("\n");

    Data data = { 0 };

    FILE *dataFile = fopen("bigData.data", "w");
    if (!dataFile)
        printf("Couldn't create file\n");

    printf("Stats:             |  TimeSPR   |  TimeBasic |   MemSPR   |  MemBasic  |TimeDiff| MemDiff \n");
    for (size_t percentile = 1; percentile <= 9; percentile += 1)
    {
        for (size_t objSize = SIZE_START; objSize <= SIZE_LIMIT; objSize += SIZE_STEP)
        {
            run(objSize, percentile, &data);
            printf("Stats:[%4lu%%,%5lu]: ", percentile, objSize);
            printf("%10lu | %10lu | %10lu | %10lu | %6.1Lf%% | %6.1Lf%% |\n",
                   data.timeRare, data.timeBasic, data.memRare, data.memBasic,
                   (((long double) data.timeBasic) / ((long double) data.timeRare) - 1) * 100,
                   (((long double) data.memBasic) / ((long double) data.memRare) - 1) * 100);
            if (dataFile)
            {
                fprintf(dataFile, "Stats:[%4lu%%,%5lu]: " "%10lu | %10lu | %10lu | %10lu | %6.1Lf%% | %6.1Lf%% |\n",
                        percentile, objSize,
                        data.timeRare, data.timeBasic, data.memRare, data.memBasic,
                        (((long double) data.timeBasic) / ((long double) data.timeRare) - 1) * 100,
                        (((long double) data.memBasic) / ((long double) data.memRare) - 1) * 100);
            }
        }
    }
    for (size_t percentile = FILL_START; percentile <= FILL_END; percentile += FILL_STEP)
    {
        for (size_t objSize = SIZE_START; objSize <= SIZE_LIMIT; objSize += SIZE_STEP)
        {
            run(objSize, percentile, &data);
            printf("Stats:[%4lu%%,%5lu]: ", percentile, objSize);
            printf("%10lu | %10lu | %10lu | %10lu | %6.1Lf%% | %6.1Lf%% |\n",
                   data.timeRare, data.timeBasic, data.memRare, data.memBasic,
                   (((long double) data.timeBasic) / ((long double) data.timeRare) - 1) * 100,
                   (((long double) data.memBasic) / ((long double) data.memRare) - 1) * 100);
            if (dataFile)
            {
                fprintf(dataFile, "Stats:[%4lu%%,%5lu]: " "%10lu | %10lu | %10lu | %10lu | %6.1Lf%% | %6.1Lf%% |\n",
                        percentile, objSize,
                        data.timeRare, data.timeBasic, data.memRare, data.memBasic,
                        (((long double) data.timeBasic) / ((long double) data.timeRare) - 1) * 100,
                        (((long double) data.memBasic) / ((long double) data.memRare) - 1) * 100);
            }
        }
    }
    printf("\n");

    if (dataFile)
        fclose(dataFile);

    return OK;
}
