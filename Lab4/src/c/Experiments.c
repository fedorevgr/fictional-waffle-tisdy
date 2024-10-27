#include "Experiments.h"

#define EMPTY_NUMBER 1

#include <time.h>
#define NANO_SEC(time) (time.tv_sec * 1e9L + time.tv_nsec)

#define LOOPS 10

#include <stdio.h>

void
experiment(double *results, Stack *stack, ListStack *listStack)
{
    FILE *file = fopen("data.csv", "w");

    if (file)
        fprintf(file, "PUSH_ARRAY_START, POP_ARRAY_START, PUSH_ARRAY_END, POP_ARRAY_END, PUSH_LIST, POP_LIST\n");

    double tmp[EXPERIMENTS];
    for (int I = 0; I < LOOPS; ++I)
    {
        tmp[PUSH_ARRAY_START] = measurePushStart(stack);
        tmp[POP_ARRAY_START] = measurePopStart(stack);
        tmp[PUSH_ARRAY_END] = measurePushEnd(stack);
        tmp[POP_ARRAY_END] = measurePopEnd(stack);
        tmp[PUSH_LIST] = measurePushList(listStack);
        tmp[POP_LIST] = measurePopList(listStack);

        for (int EXP = 0; EXP < EXPERIMENTS; ++EXP)
            results[EXP] += tmp[EXP];

        if (file)
            fprintf(file, "%lf, %lf, %lf, %lf, %lf, %lf\n",
                    tmp[PUSH_ARRAY_START], tmp[POP_ARRAY_START],
                    tmp[PUSH_ARRAY_END], tmp[POP_ARRAY_END],
                    tmp[PUSH_LIST], tmp[POP_LIST]
                    );
    }

    for (int I = 0; I < EXPERIMENTS; ++I)
    {
        results[I] /= LOOPS;
    }
    if (file)
        fclose(file);
}

double
measurePushStart(Stack *stack)
{
    struct timespec timeStart, timeEnd;

    size_t i = 0;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    for (; i < RUNS; ++i)
        stackPush(stack, EMPTY_NUMBER, FROM_START);

    clock_gettime(CLOCK_REALTIME, &timeEnd);

    return (double) (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / RUNS;
}

double
measurePopStart(Stack *stack)
{
    struct timespec timeStart, timeEnd;
    size_t i = 0;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    for (; i < RUNS; ++i)
        stackPop(stack, FROM_START, nullptr);

    clock_gettime(CLOCK_REALTIME, &timeEnd);

    return (double) (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / RUNS;
}

double
measurePushEnd(Stack *stack)
{
    struct timespec timeStart, timeEnd;

    size_t i = 0;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    for (; i < RUNS; ++i)
        stackPush(stack, EMPTY_NUMBER, FROM_END);

    clock_gettime(CLOCK_REALTIME, &timeEnd);

    return (double) (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / RUNS;
}

double
measurePopEnd(Stack *stack)
{
    struct timespec timeStart, timeEnd;
    size_t i = 0;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    for (; i < RUNS; ++i)
        stackPop(stack, FROM_END, nullptr);

    clock_gettime(CLOCK_REALTIME, &timeEnd);

    return (double) (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / RUNS;
}

double
measurePushList(ListStack *stack)
{
    struct timespec timeStart, timeEnd;
    size_t i = 0;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    for (; i < RUNS; ++i)
        lStackPush(stack, EMPTY_NUMBER);

    clock_gettime(CLOCK_REALTIME, &timeEnd);

    return (double) (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / RUNS;
}

double
measurePopList(ListStack *stack)
{
    struct timespec timeStart, timeEnd;
    size_t i = 0;
    clock_gettime(CLOCK_REALTIME, &timeStart);

    for (; i < RUNS; ++i)
        lStackPop(stack, nullptr);

    clock_gettime(CLOCK_REALTIME, &timeEnd);

    return (double) (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / RUNS;
}
