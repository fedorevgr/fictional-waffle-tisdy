#include "Measure.h"

#define TOLERANCE 0.03
#define LIMIT 100
#include <math.h>
#include "Service.h"

void
findAverage(ResultData *array, int length, size_t *averageModel, size_t *averageIdle)
{
    size_t sumModel = 0;
    size_t sumIdle = 0;
    for (int i = 0; i < length; ++i)
    {
        sumModel += array[i].timeModel;
        sumIdle += array[i].timeIdle;
    }

    *averageModel = sumModel / length;
    *averageIdle = sumIdle / length;
}

void
calculateError(ResultData *array,
               int length,
               size_t *averageModel,
               size_t *averageIdle,
               size_t *errModel,
               size_t *errIdle)
{
    findAverage(array, length, averageModel, averageIdle);

    size_t modelSquareSum = 0;
    size_t idleSquareSum = 0;

    size_t tmp;

    for (int i = 0; i < length; ++i)
    {
        tmp = array[i].timeModel - *averageModel;
        modelSquareSum += tmp * tmp;

        tmp = array[i].timeIdle - *averageIdle;
        idleSquareSum += tmp * tmp;
    }
    *errModel = (unsigned long) sqrt((double) modelSquareSum / (length * (length - 1)));
    *errIdle = (unsigned long) sqrt((double) idleSquareSum / (length * (length - 1)));
}

size_t
measure(
    size_t (*f)(size_t , size_t, bool, bool, ResultData *),
    size_t *averageResultModel,
    size_t *averageResultIdle,
    size_t *errorModel,
    size_t *errorIdle
)
{
    size_t ticks;
    *averageResultIdle = 1;
    *averageResultModel = 1;
    *errorModel = 1;
    *errorIdle = 1;

    ResultData results[LIMIT] = {0};
    ticks = f(TIME_MAX_T1, TIME_MAX_T2, 0, 0, results);

    int i = 1;
    for (; i < LIMIT && ((double) *errorModel / (double) *averageResultModel > TOLERANCE
        || (double) *errorIdle / (double) *averageResultIdle > TOLERANCE); ++i)
    {
        f(TIME_MAX_T1, TIME_MAX_T2, 0, 0, results + i);
        calculateError(results, i + 1, averageResultModel, averageResultIdle, errorModel, errorIdle);
    }

    if (i == LIMIT)
        printf("Limit reached %d\n", LIMIT);
    return ticks;
}

void
printMeasureResults(
    size_t averageResultModel,
    size_t averageResultIdle,
    size_t errorModel,
    size_t errorIdle,
    size_t ticks)
{
    printf("    Results: \n"
           "\tModeling time: %.3lf ± %.3lf ms\n"
           "\tIdle time: %.3lf ± %.3lf ms\n",
           (double) averageResultModel / M_SEC,
           (double) errorModel / M_SEC,
           (double) averageResultIdle / M_SEC,
           (double) errorIdle / M_SEC);
}

void
printEstimation(size_t ticks, size_t modelTime)
{
    double ticksToMs = (double) ticks / ((double) (modelTime) / M_SEC);

    printf("Ticks: %lu\n", ticks);
    printf("Tick to time ratio: %.2lf 1/ms\n", ticksToMs);

    size_t ticksPerRequest = ((size_t) TIME_MAX_T1 + TIME_MIN) / 2;
    size_t estimatedTicks = ticksPerRequest * POOL_LIMIT;

    printf("Average ticks per request: %lu\n", ticksPerRequest);
    printf("Estimated model time: %lu\n", estimatedTicks);
    printf("Estimated time equivalent: %.1lf\n", (double) estimatedTicks / ticksToMs);
}