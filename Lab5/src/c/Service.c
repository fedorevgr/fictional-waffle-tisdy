#include "Service.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ArrayQueue.h"
#include "ListQueue.h"

#define TIME_FACTOR 1e4
#define TIME_MIN 0
#define TIME_MAX_T1 (6 * TIME_FACTOR)
#define TIME_MAX_T2 (1 * TIME_FACTOR)

#define POOL_LIMIT 1000

long
createTimer(size_t limit)
{
    return (long) (random() % limit);
}

typedef struct InstantData_
{
    size_t averageQueueLengthSum;
    size_t averageQueueLengthAmount;
} InstantData;

static void printResult(ResultData resultData)
{
    printf("\nResults\n");
    printf("Model time: %.3lf ms\n",
           (double) resultData.timeModel / M_SEC);
    printf("Elements in: %lu, out: %lu\n", resultData.elementsIn, resultData.elementsOut);
    printf("Triggers: %lu\n", resultData.OATriggers);
    printf("Idle time: %.3lf ms\n",
           (double) resultData.timeIdle / M_SEC);
}

size_t
simulateArrayQueue(bool verbose, bool showAddresses, ResultData *results)
{
    struct timespec tmpTime, idleTmpTimeStart, idleTmpTimeEnd;
    clock_gettime(CLOCK_REALTIME, &idleTmpTimeStart);

    srand(time(nullptr));
    long poolingTimer = 0, OATimer = 0;
    size_t ticks = 0;

    size_t pooled = 0;

    Element newElement = {0};
    Element currElement = {0};

    InstantData instantData = {0};
    ResultData resultData = {0};
    size_t previousElementsOut = 0;

    bool busy = false;
    bool enqueuedInTick = false;
    QueueStatus queueStatus;
    ArrayQueue *OAQueue = createArrayQueue();
    if (!OAQueue)
        return 0;

    if (verbose)
        printf("Exited | Current | Average\n");

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime);

    while (resultData.elementsOut < POOL_LIMIT)
    {
        if (poolingTimer <= 0)
        {
            queueStatus = enqueueArray(OAQueue, newElement);

            if (queueStatus == Q_OK)
            {
                poolingTimer = createTimer(TIME_MAX_T1);
                pooled++;
                resultData.elementsIn++;

                if (showAddresses)
                    printf("Added: %p\n", OAQueue->arr + OAQueue->rear);
            }
        }
        if (OATimer <= 0)
        {
            enqueuedInTick = false;
            if (busy)
            {
                if (currElement.cycles == 5)
                    resultData.elementsOut++;
                else
                {
                    enqueueArray(OAQueue, currElement);

                    if (showAddresses)
                        printf("Added: %p\n", OAQueue->arr + OAQueue->rear);
                }

                clock_gettime(CLOCK_REALTIME, &idleTmpTimeStart);
                enqueuedInTick = true;
            }
            busy = false;

            queueStatus = dequeueArray(OAQueue, &currElement);
            if (queueStatus == Q_OK)
            {
                currElement.cycles++;

                OATimer = createTimer(TIME_MAX_T2);

                resultData.OATriggers++;
                busy = true;

                if (!enqueuedInTick)
                {
                    clock_gettime(CLOCK_REALTIME, &idleTmpTimeEnd);
                    resultData.timeIdle += NANO_SEC(idleTmpTimeEnd) - NANO_SEC(idleTmpTimeStart);
                }

                if (showAddresses)
                    printf("Removed: %p\n", OAQueue->arr + OAQueue->front);
            }
        }

        instantData.averageQueueLengthAmount++;
        instantData.averageQueueLengthSum += OAQueue->size;

        if (verbose && previousElementsOut != resultData.elementsOut && resultData.elementsOut % 100 == 0
            && resultData.elementsOut != 0)
        {
            printf("%6lu | %7d | %7lf\n",
                   resultData.elementsOut,
                   OAQueue->size,
                   (double) instantData.averageQueueLengthSum / (double) instantData.averageQueueLengthAmount);
            instantData.averageQueueLengthSum = 0;
            instantData.averageQueueLengthAmount = 0;
            previousElementsOut = resultData.elementsOut;
        }

        --poolingTimer;
        --OATimer;
        ++ticks;
    }

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime) - resultData.timeModel;

    printResult(resultData);

    *results = resultData;
    return ticks;
}

size_t
simulateListQueue(bool verbose, bool showAddresses, ResultData *results)
{
    struct timespec tmpTime, idleTmpTimeStart, idleTmpTimeEnd;
    clock_gettime(CLOCK_REALTIME, &idleTmpTimeStart);

    srand(time(nullptr));
    long poolingTimer = 0, OATimer = 0;
    size_t ticks = 0;

    size_t pooled = 0;

    Element newElement = {0};
    Element currElement = {0};

    InstantData instantData = {0};
    ResultData resultData = {0};
    size_t previousElementsOut = 0;

    bool busy = false;
    bool enqueuedInTick = false;
    QueueStatus queueStatus;
    ListQueue *OAQueue = createListQueue();
    if (!OAQueue)
        return 0;

    if (verbose)
        printf("Exited | Current | Average\n");

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime);

    while (resultData.elementsOut < POOL_LIMIT)
    {
        if (poolingTimer <= 0)
        {
            queueStatus = enqueueList(OAQueue, newElement);

            if (queueStatus == Q_OK)
            {
                poolingTimer = createTimer(TIME_MAX_T1);
                pooled++;
                resultData.elementsIn++;

                if (showAddresses)
                    printf("Added: %p\n", OAQueue->rear);
            }
        }
        if (OATimer <= 0)
        {
            enqueuedInTick = false;
            if (busy)
            {
                if (currElement.cycles == 5)
                    resultData.elementsOut++;
                else
                {
                    enqueueList(OAQueue, currElement);

                    if (showAddresses)
                        printf("Added: %p\n", OAQueue->rear);
                }

                clock_gettime(CLOCK_REALTIME, &idleTmpTimeStart);
                enqueuedInTick = true;
            }
            busy = false;

            queueStatus = dequeueList(OAQueue, &currElement);
            if (queueStatus == Q_OK)
            {
                currElement.cycles++;

                OATimer = createTimer(TIME_MAX_T2);

                resultData.OATriggers++;
                busy = true;

                if (!enqueuedInTick)
                {
                    clock_gettime(CLOCK_REALTIME, &idleTmpTimeEnd);
                    resultData.timeIdle += NANO_SEC(idleTmpTimeEnd) - NANO_SEC(idleTmpTimeStart);
                }

                if (showAddresses)
                    printf("Removed: %p\n", OAQueue->front);
            }
        }

        instantData.averageQueueLengthAmount++;
        instantData.averageQueueLengthSum += OAQueue->size;

        if (verbose && previousElementsOut != resultData.elementsOut && resultData.elementsOut % 100 == 0
            && resultData.elementsOut != 0)
        {
            printf("%6lu | %7d | %7lf\n",
                   resultData.elementsOut,
                   OAQueue->size,
                   (double) instantData.averageQueueLengthSum / (double) instantData.averageQueueLengthAmount);
            instantData.averageQueueLengthSum = 0;
            instantData.averageQueueLengthAmount = 0;
            previousElementsOut = resultData.elementsOut;
        }

        --poolingTimer;
        --OATimer;
        ++ticks;
    }

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime) - resultData.timeModel;

    printResult(resultData);

    *results = resultData;
    return ticks;
}

#define TOLERANCE 0.03
#define LIMIT 100
#include <math.h>

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
calculateError(ResultData *array, int length, size_t *averageModel, size_t *averageIdle, size_t *errModel, size_t *errIdle)
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

void
measure(
    size_t (*f)(bool, bool, ResultData *),
    size_t *averageResultModel,
    size_t *averageResultIdle,
    size_t *errorModel,
    size_t *errorIdle
)
{
    *averageResultIdle = 1;
    *averageResultModel = 1;
    *errorModel = 1;
    *errorIdle = 1;


    ResultData results[LIMIT] = {0};
    f(0, 0, results);

    int i = 1;
    for (; i < LIMIT && ((double)*errorModel / (double)*averageResultModel > TOLERANCE || (double)*errorIdle / (double) *averageResultIdle > TOLERANCE); ++i)
    {
        f(0, 0, results + i);
        calculateError(results, i + 1, averageResultModel, averageResultIdle, errorModel, errorIdle);
    }

    if (i == LIMIT)
        printf("Limit reached %d\n", LIMIT);

}

void
serviceExperiment(void)
{
    size_t averageResultModel;
    size_t averageResultIdle;
    size_t errorModel;
    size_t errorIdle;

    size_t averageResultModel2;
    size_t averageResultIdle2;
    size_t errorModel2;
    size_t errorIdle2;

    printf("Measurements:\n");
    printf("Array:\n");
    measure(simulateArrayQueue, &averageResultModel, &averageResultIdle, &errorModel, &errorIdle);
    printf("List:\n");
    measure(simulateListQueue, &averageResultModel2, &averageResultIdle2, &errorModel2, &errorIdle2);
    printf("\n\n\n\n\n\n\n\n\n\n\n"
           "Array:\n");
    printf("    Results: \n"
           "\tModeling time: %.3lf ± %.3lf ms\n"
           "\tIdle time: %.3lf ± %.3lf ms\n", // todo all in nanoseconds
           (double) averageResultModel / M_SEC,
           (double) errorModel / M_SEC,
           (double) averageResultIdle / M_SEC,
           (double) errorIdle / M_SEC);
    printf("List:\n");
    printf("    Results: \n"
           "\tModeling time: %.3lf ± %.3lf ms\n"
           "\tIdle time: %.3lf ± %.3lf ms\n", // todo all in nanoseconds
           (double) averageResultModel2 / M_SEC,
           (double) errorModel2 / M_SEC,
           (double) averageResultIdle2 / M_SEC,
           (double) errorIdle2 / M_SEC);
}
