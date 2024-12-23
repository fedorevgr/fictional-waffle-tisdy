#include "../include/ArrayQueue.h"

static
void
initAQueue(ArrayQueue *q)
{
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

#include <stdlib.h>

ArrayQueue *
createArrayQueue(void)
{
    ArrayQueue *queue = malloc(sizeof(ArrayQueue));
    if (!queue)
        return NULL;

    initAQueue(queue);

    return queue;
}

void
freeArrayQueue(ArrayQueue *queue)
{
    free(queue);
}

static
int
aIsEmpty(ArrayQueue *q)
{
    return (q->size == 0);
}

static
int
aIsFull(ArrayQueue *q)
{
    return (q->size == MAX_SIZE);
}

QueueStatus
enqueueArray(ArrayQueue *q, Element val)
{
    if (q->size == MAX_SIZE)
        return Q_FULL;

    q->rear = (q->rear + 1) % MAX_SIZE;
    q->arr[q->rear] = val;
    q->size++;
    return Q_OK;
}

QueueStatus
dequeueArray(ArrayQueue *q, Element *element)
{
    if (q->size == 0)
        return Q_EMPTY;

    Element val = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    *element = val;
    return Q_OK;
}

size_t
getArraySize(const ArrayQueue *q)
{
    return sizeof(*q);
}
