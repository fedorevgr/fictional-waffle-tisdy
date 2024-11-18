#include "Shuffle.h"
#include "BinTree.h"
#include <stdio.h>

static size_t getNanoSec(struct timespec time)
{
    return time.tv_sec * 1000000000 + time.tv_nsec;
}

#define ADD_TO_SIZE 10000
#define REPETITIONS 1000

void getAddTime(void)
{
    BinTree *tree = nullptr;

    Elem treeElements[ADD_TO_SIZE];
    for (int I = 0; I < ADD_TO_SIZE; ++I)
        treeElements[I] = I * 2;
    shuffle(treeElements, ADD_TO_SIZE, sizeof(Elem), 0);
    for (int I = 0; I < ADD_TO_SIZE; ++I)
        treeAdd(&tree, treeElements[I]);

    size_t result = 0;
    struct timespec timeStart, timeEnd;

    Elem elemArray[REPETITIONS];
    for (int I = 0; I < REPETITIONS; ++I)
        elemArray[I] = I * 2 - 1;
    shuffle(elemArray, REPETITIONS, sizeof(Elem), 0);

    for (int I = 0; I < REPETITIONS; ++I)
    {
        clock_gettime(CLOCK_REALTIME, &timeStart);
        treeFind(tree, elemArray[I]);
        clock_gettime(CLOCK_REALTIME, &timeEnd);
        result += getNanoSec(timeEnd) - getNanoSec(timeStart);
    }

    treeDestroy(tree);
    printf("Tree add time: %7.2lf\n",  (double) result / REPETITIONS);
}

void getAddFileTime(void)
{
    Elem treeElements[ADD_TO_SIZE];
    for (int I = 0; I < ADD_TO_SIZE; ++I)
        treeElements[I] = I * 2;
    shuffle(treeElements, ADD_TO_SIZE, sizeof(Elem), 0);

    size_t result = 0;
    struct timespec timeStart, timeEnd;

    Elem elemArray[REPETITIONS];
    for (int I = 0; I < REPETITIONS; ++I)
        elemArray[I] = I * 2 - 1;
    shuffle(elemArray, REPETITIONS, sizeof(Elem), 0);

    for (int I = 0; I < REPETITIONS; ++I)
    {
        clock_gettime(CLOCK_REALTIME, &timeStart);

        for (int J = 0; J < ADD_TO_SIZE; ++J)
        {
            if (treeElements[J] == elemArray[I])
            {
                J = J + 100;
                J = J - 100;
            }
        }

        clock_gettime(CLOCK_REALTIME, &timeEnd);
        result += getNanoSec(timeEnd) - getNanoSec(timeStart);
    }

    printf("File add time: %7.2lf\n",  (double) result / REPETITIONS);
}

void getRemoveFileTime(void)
{
    Elem treeElements[ADD_TO_SIZE];
    for (int I = 0; I < ADD_TO_SIZE; ++I)
        treeElements[I] = I * 2;
    shuffle(treeElements, ADD_TO_SIZE, sizeof(Elem), 0);

    size_t result = 0;
    struct timespec timeStart, timeEnd;

    Elem elemArray[REPETITIONS];
    for (int I = 0; I < REPETITIONS; ++I)
        elemArray[I] = I * 2 - 1;
    shuffle(elemArray, REPETITIONS, sizeof(Elem), 0);

    for (int I = 0; I < REPETITIONS; ++I)
    {
        clock_gettime(CLOCK_REALTIME, &timeStart);

        for (int J = 0; J < ADD_TO_SIZE; ++J)
        {
            if (treeElements[J] == elemArray[I])
            {
                J = J + 100;
                J = J - 100;
            }
        }

        clock_gettime(CLOCK_REALTIME, &timeEnd);
        result += getNanoSec(timeEnd) - getNanoSec(timeStart);
    }

    printf("File remove time: %7.2lf\n",  (double) result / REPETITIONS);
}

void getRemoveTime(void)
{
    BinTree *tree = nullptr;

    Elem treeElements[ADD_TO_SIZE];
    for (int I = 0; I < ADD_TO_SIZE; ++I)
        treeElements[I] = I * 2;
    shuffle(treeElements, ADD_TO_SIZE, sizeof(Elem), 0);
    for (int I = 0; I < ADD_TO_SIZE; ++I)
        treeAdd(&tree, treeElements[I]);

    size_t result = 0;
    struct timespec timeStart, timeEnd;

    Elem elemArray[REPETITIONS];
    for (int I = 0; I < REPETITIONS; ++I)
        elemArray[I] = I * 2 - 1;
    shuffle(elemArray, REPETITIONS, sizeof(Elem), 0);

    for (int I = 0; I < REPETITIONS; ++I)
    {
        clock_gettime(CLOCK_REALTIME, &timeStart);
        treeFind(tree, elemArray[I]);
        clock_gettime(CLOCK_REALTIME, &timeEnd);
        result += getNanoSec(timeEnd) - getNanoSec(timeStart);
    }

    treeDestroy(tree);
    printf("Tree remove time: %7.2lf\n",  (double) result / REPETITIONS);
}
