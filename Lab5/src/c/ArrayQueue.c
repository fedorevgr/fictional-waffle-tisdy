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

ExitCode
enqueueArray(ArrayQueue *q, Element val)
{
    if (aIsFull(q))
        return ERROR;

    q->rear = (q->rear + 1) % MAX_SIZE;
    q->arr[q->rear] = val;
    q->size++;
    return OK;
}

Element
dequeueArray(ArrayQueue *q)
{
    if (aIsEmpty(q))
        return (Element) { 0 };

    Element val = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return val;
}

