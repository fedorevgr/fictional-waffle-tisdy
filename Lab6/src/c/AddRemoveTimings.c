#include "Shuffle.h"
#include "BinTree.h"
#include <stdio.h>
#include "File.h"

#define ADD_TO_SIZE 10000
#define REPETITIONS 1000

static size_t getNanoSec(struct timespec time)
{
    return time.tv_sec * 1000000000 + time.tv_nsec;
}

int getSize(void)
{
    return ADD_TO_SIZE;
}

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

        BinTree *newElem = malloc(sizeof(BinTree));
        treeFind(tree, elemArray[I]);

        clock_gettime(CLOCK_REALTIME, &timeEnd);
        free(newElem);
        result += getNanoSec(timeEnd) - getNanoSec(timeStart);
    }

    treeDestroy(tree);
    printf("Tree add time: %7.2lf\n",  (double) result / REPETITIONS);
}

#define STATS_FILE_NAME "test.txt"

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
        writeFile(STATS_FILE_NAME, treeElements, ADD_TO_SIZE);

        clock_gettime(CLOCK_REALTIME, &timeStart);

        addToFile(STATS_FILE_NAME, elemArray[I]);

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
        writeFile(STATS_FILE_NAME, treeElements, ADD_TO_SIZE);

        clock_gettime(CLOCK_REALTIME, &timeStart);

        removeFromFile(STATS_FILE_NAME, elemArray[I]);

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
        BinTree *newElem = malloc(sizeof(BinTree));

        clock_gettime(CLOCK_REALTIME, &timeStart);

        treeFind(tree, elemArray[I]);
        free(newElem);

        clock_gettime(CLOCK_REALTIME, &timeEnd);


        result += getNanoSec(timeEnd) - getNanoSec(timeStart);
    }

    treeDestroy(tree);
    printf("Tree remove time: %7.2lf\n",  (double) result / REPETITIONS);
}
