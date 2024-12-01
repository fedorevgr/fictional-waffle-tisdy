#include "StatsService.h"

#include "BinTree/BinTree.h"
#include "BinTree/BinTreeEtc.h"
#include "HashMap/HashMapPrivate.h"
#include "HashMap/HashMapPublic.h"
#include "File.h"

#include "IterCounters.h"

#include "etc/Shuffle.h"
#include "IterCounters.h"

#include <stdio.h>
#include <time.h>

#define STARTING_SIZE 10
#define SIZE_STEP 50
#define SIZE_LIMIT 1010

#define REPETITIONS 20

#define PRECISION 1000

typedef struct Stat_
{
    double time;
    double iter;
    double memory;
} Stat;

typedef struct StatUL
{
    size_t time;
    size_t iter;
    size_t memory;
} StatUnsignedLong;

typedef struct Stats_
{
    StatUnsignedLong regTree;
    StatUnsignedLong avlTree;
    StatUnsignedLong pubHash;
    StatUnsignedLong priHash;
    StatUnsignedLong file;
} Stats;

static size_t getNanoSec(struct timespec time)
{
    return time.tv_sec * 1000000000 + time.tv_nsec;
}

static void runRepetitions(int size)
{
    struct timespec timeStart, timeEnd;

    Stats concludingStats = { 0 };

    int *elements = calloc(size, sizeof(int));

    BinTree *regularTree, *avlTree;
    HashMapPrivate *hashPrivate;
    HashMapPub *hashPublic;
    const char *filename = "TestsStats.txt";

    for (int J = 0; J < REPETITIONS; ++J)
    {
        regularTree = nullptr, avlTree = nullptr, hashPrivate = hashPriMapInit(INIT_SIZE), hashPublic = hashPubMapInit(INIT_SIZE);
        for (int I = 0; I < size; elements[I] = I, ++I);
        shuffle(elements, size, sizeof(int), 1);

        for (int I = 0, elem; I < size; ++I)
        {
            elem = elements[I];
            treeAdd(&regularTree, elem, false);
            treeAdd(&avlTree, elem, true);
            hashPubMapAdd(&hashPublic, elem);
            hashPriMapAdd(&hashPrivate, elem);
            writeFile(filename, elements, size);
        }

        Stats repStats = { 0 };
        counterGet();
        for (int I = 0; I < size; ++I)
        {
            clock_gettime(CLOCK_REALTIME, &timeStart);
            treeFind(regularTree, I);
            clock_gettime(CLOCK_REALTIME, &timeEnd);
            repStats.regTree.time += getNanoSec(timeEnd) - getNanoSec(timeStart);
            repStats.regTree.iter += counterGet();
            repStats.regTree.memory += treeTraverse(regularTree, ORDER_IN, nullptr, nullptr) * sizeof(BinTree);

            clock_gettime(CLOCK_REALTIME, &timeStart);
            treeFind(avlTree, I);
            clock_gettime(CLOCK_REALTIME, &timeEnd);
            repStats.avlTree.time += getNanoSec(timeEnd) - getNanoSec(timeStart);
            repStats.avlTree.iter += counterGet();
            repStats.avlTree.memory += treeTraverse(avlTree, ORDER_IN, nullptr, nullptr) * sizeof(BinTree);

            clock_gettime(CLOCK_REALTIME, &timeStart);
            hashPriMapIn(hashPrivate, I);
            clock_gettime(CLOCK_REALTIME, &timeEnd);
            repStats.priHash.time += getNanoSec(timeEnd) - getNanoSec(timeStart);
            repStats.priHash.iter += counterGet();
            repStats.priHash.memory += hashPriSize(hashPrivate);

            clock_gettime(CLOCK_REALTIME, &timeStart);
            hashPubMapIn(hashPublic, I);
            clock_gettime(CLOCK_REALTIME, &timeEnd);
            repStats.pubHash.time += getNanoSec(timeEnd) - getNanoSec(timeStart);
            repStats.pubHash.iter += counterGet();
            repStats.pubHash.memory += hashPubSize(hashPublic);

            clock_gettime(CLOCK_REALTIME, &timeStart);
            fileFind(filename, I);
            clock_gettime(CLOCK_REALTIME, &timeEnd);
            repStats.file.time += getNanoSec(timeEnd) - getNanoSec(timeStart);
            repStats.file.iter += counterGet();
            repStats.file.memory += fileSize(filename);
        }

        concludingStats.regTree.time += repStats.regTree.time / size;
        concludingStats.regTree.iter += repStats.regTree.iter / size;
        concludingStats.regTree.memory += repStats.regTree.memory / size;

        concludingStats.avlTree.time += repStats.avlTree.time / size;
        concludingStats.avlTree.iter += repStats.avlTree.iter / size;
        concludingStats.avlTree.memory += repStats.avlTree.memory / size;

        concludingStats.priHash.time += repStats.priHash.time / size;
        concludingStats.priHash.iter += repStats.priHash.iter / size;
        concludingStats.priHash.memory += repStats.priHash.memory / size;

        concludingStats.pubHash.time += repStats.pubHash.time / size;
        concludingStats.pubHash.iter += repStats.pubHash.iter / size;
        concludingStats.pubHash.memory += repStats.pubHash.memory / size;

        concludingStats.file.time += repStats.file.time / size;
        concludingStats.file.iter += repStats.file.iter / size;
        concludingStats.file.memory += repStats.file.memory / size;

        treeDestroy(regularTree), treeDestroy(avlTree), hashPriMapDestroy(hashPrivate), hashPubMapDestroy(hashPublic);
    }
    free(elements);

    printf(" %7.1lf | %7.3lf | %7.1lf |", (double )concludingStats.regTree.time / REPETITIONS, (double )concludingStats.regTree.iter / REPETITIONS, (double )concludingStats.regTree.memory / REPETITIONS);
    printf(" %7.1lf | %7.3lf | %7.1lf |", (double )concludingStats.avlTree.time / REPETITIONS, (double )concludingStats.avlTree.iter / REPETITIONS, (double )concludingStats.avlTree.memory / REPETITIONS);
    printf(" %7.1lf | %7.3lf | %7.1lf |", (double )concludingStats.pubHash.time / REPETITIONS, (double )concludingStats.pubHash.iter / REPETITIONS, (double )concludingStats.pubHash.memory / REPETITIONS);
    printf(" %7.1lf | %7.5lf | %7.1lf |", (double )concludingStats.priHash.time / REPETITIONS, (double )concludingStats.priHash.iter / REPETITIONS, (double )concludingStats.priHash.memory / REPETITIONS);
    printf(" %7.1lf | %7.3lf | %7.1lf |\n", (double )concludingStats.file.time / REPETITIONS, (double )concludingStats.file.iter / REPETITIONS, (double )concludingStats.file.memory / REPETITIONS);
}

static void runStats(void)
{
    Stat stat;

    for (int I = STARTING_SIZE; I < SIZE_LIMIT; I += SIZE_STEP)
    {
        printf("| %5d |", I);

        runRepetitions(I);

        printf("\n");
    }
}

static void preLoad(void)
{
    const char *filename = "TestsStats.txt";
    int size = REPETITIONS;
    int *elements = calloc(size, sizeof(int));

    for (int J = 0; J < REPETITIONS; ++J)
    {
        for (int I = 0; I < size; elements[I] = I, ++I);
        shuffle(elements, size, sizeof(int), 1);

        writeFile(filename, elements, size);
    }
    free(elements);
}

void serviceStatistics(void)
{
    preLoad();

    srand(time(nullptr));

    printf("\n\nAverage find time (ms), comparisons, memory (bytes)\n\n");

    printf("| %5s | %27s | %27s | %27s | %27s | %27s |\n| %5s |", "", "Regular Binary Tree", "AVL Tree", "Public hashing", "Private hashing", "File", "");
    for (int I = 0; I < 5; ++I)
        printf(" %7s | %7s | %7s |", "time", "comp", "memo");
    printf("\n\n");

    runStats();
}
