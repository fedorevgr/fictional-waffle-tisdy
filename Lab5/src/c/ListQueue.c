
#include "../include/ListQueue.h"

#include <stdio.h>
#include <stdlib.h>

static
void
initLQueue(ListQueue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

ListQueue *
createListQueue(void)
{
    ListQueue *q = malloc(sizeof(ListQueue));
    if (!q)
        return NULL;

    initLQueue(q);
    return q;
}

void
freeListQueue(ListQueue *q)
{
    Node *node = q->front, *next;
    while (node)
    {
        next = node->next;
        free(node);
        node = next;
    }
    free(q);
}

static
int
lIsEmpty(ListQueue *q)
{
    return (q->front == NULL);
}

QueueStatus
enqueueList(ListQueue *q, Element value)
{
    Node *newNode = malloc(sizeof(Node));

    if (!newNode)
        return Q_FULL;

    newNode->data = value;
    newNode->next = NULL;

    if (lIsEmpty(q))
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return Q_OK;
}

QueueStatus
dequeueList(ListQueue *q, Element *element)
{
    if (lIsEmpty(q))
        return Q_EMPTY;

    Element value = q->front->data;
    Node *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
    *element = value;
    return Q_OK;
}

