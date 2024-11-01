#include "Service.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ArrayQueue.h"

#define TIME_FACTOR 1e6
#define TIME_MIN 0
#define TIME_MAX_T1 (6 * TIME_FACTOR)
#define TIME_MAX_T2 (1 * TIME_FACTOR)

#define POOL_LIMIT 100

long createTimer(size_t limit)
{
    return random() % limit;
}


size_t simulateArrayQueue(void)
{
    srand(time(NULL));
    QueueStatus queueStatus;
    long poolingTimer = 0, OATimer = 0;
    size_t ticks = 0;
    size_t pooled = 0;
    Element newElement = { 0 };
    Element currElement = { 0 };

    ArrayQueue *OAQueue = createArrayQueue();
    if (!OAQueue)
        return 0;
    // todo
    while (OAQueue->size > 0)
    {
        if (poolingTimer == 0 && pooled <= POOL_LIMIT)
        {
            pooled++;
            queueStatus = enqueueArray(OAQueue, newElement);
            poolingTimer = createTimer(TIME_MAX_T1);
        }
        if (OATimer == 0)
        {
            queueStatus = dequeueArray(OAQueue, nullptr);

            if (queueStatus == Q_OK)
            {
                if (currElement.cycles != 5)
                {
                    currElement.cycles++;
                    queueStatus = enqueueArray(OAQueue, currElement);
                    OATimer = createTimer(TIME_MAX_T2);
                }
            }
            // else aboba
        }

        --poolingTimer;
        --OATimer;
        ++ticks;
    }
    return ticks;
}
