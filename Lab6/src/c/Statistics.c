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

static void fillArraySequence(Elem *elemArray, size_t length)
{
    for (int I = 0; I < length; ++I)
        elemArray[I] = I;
}

BinTree *treeFromArray(Elem *array, size_t length)
{
    BinTree *tree = nullptr;
    for (size_t I = 0; I < length; ++I)
    {
        treeAdd(&tree, array[I]);
    }
    return tree;
}
#define EPS 0.01
#define MICROSECONDS_FACTOR 1000

void runRepetitions(Elem *elemArray, size_t depth)
{
    BinTree *tree;
    Elem toFind = 1;
    size_t resSort = 0;
    size_t resFind = 0;
    struct timespec timeStart, timeEnd;

    for (int branching = 0; branching <= BRANCHING_LEVELS; branching++)
    {
        fillArraySequence(elemArray, depth);

        for (int i = 0; i < REPETITIONS; ++i)
        {
            shuffle(
                elemArray,
                depth,
                sizeof(Elem),
                1 - (double) branching / BRANCHING_LEVELS);

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

        printf("%9.2lf | %9.2lf | ",
               (double) resSort / MICROSECONDS_FACTOR,
               (double) resFind / MICROSECONDS_FACTOR);
    }
}

int getSize(void);
void getRemoveTime(void);
void getRemoveFileTime(void);
void getAddFileTime(void);
void getAddTime(void);


void showStats(void)
{
    srand(time(nullptr));
    Elem elemArray[MAX_DEPTH] = { 0 };

    printf("Time units - mks, memory units - bytes\n");
    printf("Depth |");
    for (int branching = 0; branching <= BRANCHING_LEVELS; branching++)
        printf(" Sort  %2.1f | Find  %2.1f |", 1 - (double) branching / BRANCHING_LEVELS, 1 - (double) branching / BRANCHING_LEVELS);
    printf(" memory\n");
    for (size_t depth = STEP; depth <= MAX_DEPTH; depth += STEP)
    {
        printf("%5lu | ", depth);
        runRepetitions(elemArray, depth);
        printf(" %lu\n", depth * sizeof(BinTree));
    }

    printf("Elements in tree: %d\n", getSize());
    getAddTime();
    getAddFileTime();
    getRemoveTime();
    getRemoveFileTime();
}
