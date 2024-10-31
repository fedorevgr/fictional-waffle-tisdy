
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

ExitCode
enqueueList(ListQueue *q, Element value)
{
    Node *newNode = malloc(sizeof(Node));

    if (!newNode)
        return ERROR;

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
    return OK;
}

Element
dequeueList(ListQueue *q)
{
    if (lIsEmpty(q))
        return (Element) { 0 };

    Element value = q->front->data;
    Node *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

