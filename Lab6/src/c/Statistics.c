#include "Statistics.h"

#include "BinTree.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "Shuffle.h"

static size_t getNanoSec(struct timespec time)
{
    return time.tv_sec * 1000000000 + time.tv_nsec;
}

#define MAX_DEPTH 10000
#define STEP 100
#define REPETITIONS 100

BinTree *treeFromArray(Elem *array, size_t length)
{
    BinTree *tree = nullptr;
    for (size_t I = 0; I < length; ++I)
    {
        treeAdd(&tree, array[I]);
    }
    return tree;
}

#define MICROSECONDS_FACTOR 1000

void runRepetitions(Elem *elemArray, size_t depth)
{
    BinTree *tree;
    Elem toFind = 1;
    size_t resSort = 0;
    size_t resFind = 0;
    struct timespec timeStart, timeEnd;

    for (int i = 0; i < REPETITIONS; ++i)
    {
        shuffle(elemArray, depth, sizeof(Elem));
        tree = treeFromArray(elemArray, depth);

        clock_gettime(CLOCK_REALTIME, &timeStart);
        treeTraverse(tree, ORDER_IN, nullptr, nullptr);
        clock_gettime(CLOCK_REALTIME, &timeEnd);

        resSort += getNanoSec(timeEnd) - getNanoSec(timeStart);

        clock_gettime(CLOCK_REALTIME, &timeStart);
        treeFind(tree, toFind);
        clock_gettime(CLOCK_REALTIME, &timeEnd);

        resFind += getNanoSec(timeEnd) - getNanoSec(timeStart);

        treeDestroy(tree);
    }
    resSort /= REPETITIONS;
    resFind /= REPETITIONS;

    printf("%5lu | %7.2lf | %7.2lf\n",
           depth,
           (double) resSort / MICROSECONDS_FACTOR,
           (double) resFind / MICROSECONDS_FACTOR);
}

void getRemoveTime(void);
void getRemoveFileTime(void);
void getAddFileTime(void);
void getAddTime(void);


void showStats(void)
{
    srand(time(nullptr));
    Elem elemArray[MAX_DEPTH] = { 0 };
    for (int I = 0; I < MAX_DEPTH; ++I)
        elemArray[I] = I;

    printf("Depth | Sort    | Find\n");
    for (size_t depth = STEP; depth <= MAX_DEPTH; depth += STEP)
    {
        runRepetitions(elemArray, depth);
    }

    getAddTime();
    getAddFileTime();
    getRemoveTime();
    getRemoveFileTime();
}
