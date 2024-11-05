#include "Service.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ArrayQueue.h"
#include "ListQueue.h"


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


static void
printResult(ResultData resultData, size_t ticks)
{
    printf("\nResults\n");
    printf("Model time: %.3lf ms\n",
           (double) resultData.timeModel / M_SEC);
    printf("Elements in: %lu, out: %lu\n", resultData.elementsIn, resultData.elementsOut);
    printf("Triggers: %lu\n", resultData.OATriggers);
    printf("Idle time: %.3lf ms\n",
           (double) resultData.timeIdle / M_SEC);
}

static void
printInstantData(InstantData instantData, int size, size_t elemOut)
{
    printf("%6lu | %7d | %7lf |",
           elemOut,
           size,
           (double) instantData.averageQueueLengthSum / (double) instantData.averageQueueLengthAmount);
}

size_t
simulateArrayQueue(size_t maxPoolTime, size_t maxServeTime, bool verbose, bool showAddresses, ResultData *results)
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
    Element *enqueuedElement, *dequeuedElement;
    if (!OAQueue)
        return 0;

    if (verbose)
        printf("Exited | Current | Average  | Mem\n");

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime);

    while (resultData.elementsOut < POOL_LIMIT)
    {
        if (poolingTimer <= 0 && (maxServeTime < maxPoolTime || pooled < POOL_LIMIT))
        {
            enqueuedElement = OAQueue->arr + OAQueue->rear + 1;
            queueStatus = enqueueArray(OAQueue, newElement);

            if (queueStatus == Q_OK)
            {
                poolingTimer = createTimer(maxPoolTime);
                pooled++;
                resultData.elementsIn++;

                if (showAddresses)
                    printf("Added: %p\n", enqueuedElement);
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
                    enqueuedElement = OAQueue->arr + OAQueue->rear + 1;
                    enqueueArray(OAQueue, currElement);

                    if (showAddresses)
                        printf("Added: %p\n", enqueuedElement);
                }

                clock_gettime(CLOCK_REALTIME, &idleTmpTimeStart);
                enqueuedInTick = true;
            }
            busy = false;

            dequeuedElement = OAQueue->arr + OAQueue->front;
            queueStatus = dequeueArray(OAQueue, &currElement);
            if (queueStatus == Q_OK)
            {
                currElement.cycles++;

                OATimer = createTimer(maxServeTime);

                resultData.OATriggers++;
                busy = true;

                if (!enqueuedInTick)
                {
                    clock_gettime(CLOCK_REALTIME, &idleTmpTimeEnd);
                    resultData.timeIdle += NANO_SEC(idleTmpTimeEnd) - NANO_SEC(idleTmpTimeStart);
                }

                if (showAddresses)
                    printf("Removed: %p\n", dequeuedElement);
            }
        }

        instantData.averageQueueLengthAmount++;
        instantData.averageQueueLengthSum += OAQueue->size;

        if (verbose && previousElementsOut != resultData.elementsOut && resultData.elementsOut % 100 == 0
            && resultData.elementsOut != 0)
        {
            printInstantData(instantData, OAQueue->size, resultData.elementsOut);
            printf(" %lu\n", getArraySize(OAQueue));

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

    printResult(resultData, ticks);

    *results = resultData;
    freeArrayQueue(OAQueue);
    return ticks;
}

size_t
simulateListQueue(size_t maxPoolTime, size_t maxServeTime, bool verbose, bool showAddresses, ResultData *results)
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
    Node *enqueuedElement, *dequeuedElement;
    if (!OAQueue)
        return 0;

    if (verbose)
        printf("Exited | Current | Average  | Mem\n");

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime);

    while (resultData.elementsOut < POOL_LIMIT)
    {
        if (poolingTimer <= 0 && (maxServeTime < maxPoolTime || pooled < POOL_LIMIT))
        {
            queueStatus = enqueueList(OAQueue, newElement);

            if (queueStatus == Q_OK)
            {
                poolingTimer = createTimer(maxPoolTime);
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

            dequeuedElement = OAQueue->front;
            queueStatus = dequeueList(OAQueue, &currElement);
            if (queueStatus == Q_OK)
            {
                currElement.cycles++;

                OATimer = createTimer(maxServeTime);

                resultData.OATriggers++;
                busy = true;

                if (!enqueuedInTick)
                {
                    clock_gettime(CLOCK_REALTIME, &idleTmpTimeEnd);
                    resultData.timeIdle += NANO_SEC(idleTmpTimeEnd) - NANO_SEC(idleTmpTimeStart);
                }

                if (showAddresses)
                    printf("Removed: %p\n", dequeuedElement);
            }
        }

        instantData.averageQueueLengthAmount++;
        instantData.averageQueueLengthSum += OAQueue->size;

        if (verbose && previousElementsOut != resultData.elementsOut && resultData.elementsOut % 100 == 0
            && resultData.elementsOut != 0)
        {
            printInstantData(instantData, OAQueue->size, resultData.elementsOut);
            printf(" %lu\n", getListSize(OAQueue));

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

    printResult(resultData, ticks);

    *results = resultData;
    freeListQueue(OAQueue);
    return ticks;
}

#include "Measure.h"

void
serviceMeasureFIFO(void);

void
serviceExperiment(void)
{
    serviceMeasureFIFO();

    size_t averageResultModel;
    size_t averageResultIdle;
    size_t errorModel;
    size_t errorIdle;
    size_t ticks;

    size_t averageResultModel2;
    size_t averageResultIdle2;
    size_t errorModel2;
    size_t errorIdle2;
    size_t ticks2;

    printf("Measurements:\n");

    printf("Array:\n");
    ticks = measure(simulateArrayQueue, &averageResultModel, &averageResultIdle, &errorModel, &errorIdle);

    printf("List:\n");
    ticks2 = measure(simulateListQueue, &averageResultModel2, &averageResultIdle2, &errorModel2, &errorIdle2);

    printf("\n\n\n\n\n\n\n\n\n\n\n"
           "Array:\n");
    printMeasureResults(averageResultModel, averageResultIdle, errorModel, errorIdle, ticks);
    printEstimation(ticks, averageResultModel);
    printf("Memory: %lu\n", 3 * sizeof(int) + MAX_SIZE * sizeof(Element));

    printf("List:\n");
    printMeasureResults(averageResultModel2, averageResultIdle2, errorModel2, errorIdle2, ticks2);
    printEstimation(ticks2, averageResultModel2);
    printf("Memory:\n  Min - %lu\n  Max - %lu\n", sizeof(ListQueue), sizeof(ListQueue) + 1000 * sizeof(Node));
}

#define LOOPS 1000

void
serviceMeasureFIFO(void)
{
    ArrayQueue *startQueue = createArrayQueue();
    int i = 0;
    for (; i < LOOPS; ++i)
        enqueueArray(startQueue, (Element) { 0 });
    freeArrayQueue(startQueue);

    struct timespec timeStart, timeEnd;
    Element elementBuff;

    struct TimeResults {
        size_t arrayEnqueue;
        size_t arrayDequeue;
        size_t listEnqueue;
        size_t listDequeue;
    } timeResults = { 0 };

    ArrayQueue *arrayQueue = createArrayQueue();

    clock_gettime(CLOCK_REALTIME, &timeStart);
    for (i = 0; i < LOOPS; ++i)
        enqueueArray(arrayQueue, (Element) { 0 });
    clock_gettime(CLOCK_REALTIME, &timeEnd);

    timeResults.arrayEnqueue = (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / LOOPS;


    clock_gettime(CLOCK_REALTIME, &timeStart);
    for (i = 0; i < LOOPS; ++i)
        dequeueArray(arrayQueue, &elementBuff);
    clock_gettime(CLOCK_REALTIME, &timeEnd);


    timeResults.arrayDequeue = (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / LOOPS;

    freeArrayQueue(arrayQueue);

    ListQueue *listQueue = createListQueue();

    clock_gettime(CLOCK_REALTIME, &timeStart);
    for (i = 0; i < LOOPS; ++i)
        enqueueList(listQueue, (Element) { 0 });
    clock_gettime(CLOCK_REALTIME, &timeEnd);

    timeResults.listEnqueue = (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / LOOPS;

    clock_gettime(CLOCK_REALTIME, &timeStart);
    for (i = 0; i < LOOPS; ++i)
        dequeueList(listQueue, &elementBuff);
    clock_gettime(CLOCK_REALTIME, &timeEnd);

    timeResults.listDequeue = (NANO_SEC(timeEnd) - NANO_SEC(timeStart)) / LOOPS;

    freeListQueue(listQueue);

    printf("Put, get measurements:\n"
           "Array put - %lu ns\n"
           "Array get - %lu ns\n"
           "List put - %lu ns\n"
           "List get - %lu ns\n",
           timeResults.arrayEnqueue, timeResults.arrayDequeue, timeResults.listEnqueue, timeResults.listDequeue);
}
