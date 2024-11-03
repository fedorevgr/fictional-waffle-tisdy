#include "Service.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ArrayQueue.h"
#include "ListQueue.h"

#define TIME_FACTOR 1e6
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

    printf("\nResults\n");
    printf("Model time: %lu.%lu.%lu s\n",
           SEC(resultData.timeModel),
           MILLI_SEC(resultData.timeModel) % 1000,
           MICRO_SEC(resultData.timeModel) % 1000);
    printf("Elements in: %lu, out: %lu\n", resultData.elementsIn, resultData.elementsOut);
    printf("Triggers: %lu\n", resultData.OATriggers);
    printf("Idle time: %lu.%lu.%lu s\n",
           SEC(resultData.timeIdle),
           MILLI_SEC(resultData.timeIdle) % 1000,
           MICRO_SEC(resultData.timeIdle) % 1000);

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

    printf("\nResults\n");
    printf("Model time: %lu.%lu.%lu s\n",
           SEC(resultData.timeModel),
           MILLI_SEC(resultData.timeModel) % 1000,
           MICRO_SEC(resultData.timeModel) % 1000);
    printf("Elements in: %lu, out: %lu\n", resultData.elementsIn, resultData.elementsOut);
    printf("Triggers: %lu\n", resultData.OATriggers);
    printf("Idle time: %lu.%lu.%lu s\n",
           SEC(resultData.timeIdle),
           MILLI_SEC(resultData.timeIdle) % 1000,
           MICRO_SEC(resultData.timeIdle) % 1000);

    *results = resultData;
    return ticks;
}

#define TOLERANCE 0.03
#define LIMIT 100

void
calculateError(ResultData *array, int length, double *errModel, double *errIdle)
{

    for (int i = 0; i < length; ++i)
    {

    }

}

size_t
measure(size_t (*f)(bool, bool, ResultData *), ResultData *averageResult, double *errorModel, double *errorIdle)
{
    size_t ticks = 0;
    *errorModel = 1;
    *errorIdle = 1;

    ResultData results[LIMIT] = {0};
    ticks += f(0, 0, results);

    int i = 1;
    for (; i < LIMIT && (*errorModel > TOLERANCE || *errorIdle > TOLERANCE); ++i)
    {
        ticks += f(0, 0, results + i);

    }

    if (i == LIMIT)
        printf("Limit reached\n");

}

void
serviceExperiment(void)
{

}
