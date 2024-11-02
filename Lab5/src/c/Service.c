#include "Service.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ArrayQueue.h"

#define NSEC 1000000000
#define MKSEC 1000000
#define MSEC 1000

#define NANO_SEC(time) (time.tv_sec * 1000000000 + time.tv_nsec)

#define TIME_FACTOR 1e6
#define TIME_MIN 0
#define TIME_MAX_T1 (6 * TIME_FACTOR)
#define TIME_MAX_T2 (1 * TIME_FACTOR)

#define POOL_LIMIT 100

long
createTimer(size_t limit)
{
    return random() % limit;
}

typedef struct InstantData_
{
    size_t currentQueue;
    size_t averageQueue;
} InstantData;

typedef struct RData_
{
    size_t timeModel;
    size_t elementsIn;
    size_t elementsOut;
    size_t OATriggers;
    size_t timeIdle;
} ResultData;

size_t
simulateArrayQueue(void)
{
    struct timespec tmpTime;

    srand(time(NULL));
    QueueStatus queueStatus;
    long poolingTimer = 0, OATimer = 0;
    size_t ticks = 0;
    size_t pooled = 0;
    Element newElement = {0};
    Element currElement = {0};
    bool busy = false;
    ResultData resultData = { 0 };

    ArrayQueue *OAQueue = createArrayQueue();
    if (!OAQueue)
        return 0;

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime);

    while (resultData.elementsOut != 100)
    {
        if (poolingTimer <= 0 && pooled <= POOL_LIMIT)
        {
            queueStatus = enqueueArray(OAQueue, newElement);

            if (queueStatus == Q_OK)
            {
                poolingTimer = createTimer(TIME_MAX_T1);
                pooled++;
                resultData.elementsIn++;
            }
        }
        if (OATimer <= 0)
        {
            if (busy)
            {
                if (currElement.cycles == 5)
                    resultData.elementsOut++;
                else
                    enqueueArray(OAQueue, currElement);
            }
            busy = false;

            queueStatus = dequeueArray(OAQueue, &currElement);
            if (queueStatus == Q_OK)
            {
                resultData.OATriggers++;

                currElement.cycles++;

                OATimer = createTimer(TIME_MAX_T2);
                busy = true;
            }
        }

        // printf("%lu\n", pooled);
        --poolingTimer;
        --OATimer;
        ++ticks;
    }

    clock_gettime(CLOCK_REALTIME, &tmpTime);
    resultData.timeModel = NANO_SEC(tmpTime) - resultData.timeModel;

    printf("%lu.%lu ms\n", resultData.timeModel / MKSEC, (resultData.timeModel % MKSEC) / 1000);

    return ticks;
}
