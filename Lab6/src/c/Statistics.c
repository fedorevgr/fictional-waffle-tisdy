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

#define MICROSECONDS_FACTOR 1000

void runRepetitions(Elem *elemArray, size_t depth)
{
    BinTree *tree;
    size_t resSort = 0;
    size_t resFind = 0;
    size_t curFindTime = 0;
    struct timespec timeStart, timeEnd;

    for (int branching = 0; branching <= BRANCHING_LEVELS; branching++)
    {
        for (int i = 0; i < REPETITIONS; ++i)
        {
            fillArraySequence(elemArray, depth);

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

            curFindTime = 0;
            for (int I = 0; I < depth; ++I)
            {
                clock_gettime(CLOCK_REALTIME, &timeStart);
                treeFind(tree, elemArray[I]);
                clock_gettime(CLOCK_REALTIME, &timeEnd);

                curFindTime += getNanoSec(timeEnd) - getNanoSec(timeStart);
            }
            resFind += curFindTime / depth;

            treeDestroy(tree);
        }
        resSort /= REPETITIONS;
        resFind /= REPETITIONS;

        printf("%9.2lf | %9.2lf | ",
               (double) resSort / MICROSECONDS_FACTOR,
               (double) resFind / MICROSECONDS_FACTOR);
    }
}

#define BRANCHING_ELEM_AMOUNT 500

void branchingToLevels(void)
{
    Elem elements[BRANCHING_ELEM_AMOUNT];
    BinTree *tree;
    int *layersBuffer = calloc(BRANCHING_ELEM_AMOUNT, sizeof(int));
    size_t layerCount;

    printf("%d elems average tree height, from branching\n", BRANCHING_ELEM_AMOUNT);
    printf("Layers|");
    for (int branching = 0; branching <= BRANCHING_LEVELS; branching++)
    {
        layerCount = 0;

        for (int i = 0; i < REPETITIONS; ++i)
        {
            fillArraySequence(elements, BRANCHING_ELEM_AMOUNT);

            shuffle(
                elements,
                BRANCHING_ELEM_AMOUNT,
                sizeof(Elem),
                1 - (double) branching / BRANCHING_LEVELS);

            tree = treeFromArray(elements, BRANCHING_ELEM_AMOUNT);

            layerCount += treeLayers(tree, layersBuffer);
            treeDestroy(tree);
        }
        printf("  %20.2lf |", (double ) layerCount / REPETITIONS);
    }
    printf("\n");
    free(layersBuffer);
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
    printf("Elems |");
    for (int branching = 0; branching <= BRANCHING_LEVELS; branching++)
        printf(" Sort  %2.1f | Find  %2.1f |", 1 - (double) branching / BRANCHING_LEVELS, 1 - (double) branching / BRANCHING_LEVELS);
    printf(" memory\n");
    for (size_t depth = STEP; depth <= MAX_DEPTH; depth += STEP)
    {
        printf("%5lu | ", depth);
        runRepetitions(elemArray, depth);
        printf(" %lu\n", depth * sizeof(BinTree));
    }
    branchingToLevels();

    printf("Elements in tree: %d\n", getSize());
    getAddTime();
    getAddFileTime();
    getRemoveTime();
    getRemoveFileTime();
}
