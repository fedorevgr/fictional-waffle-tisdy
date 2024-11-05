#ifndef LAB5_SRC_C_ARRAYQUEUE_H
#define LAB5_SRC_C_ARRAYQUEUE_H

#include "QueueElement.h"
#include "ExitCodes.h"

#define MAX_SIZE 200000


typedef struct {
    Element arr[MAX_SIZE];
    int front;
    int rear;
    int size;
} ArrayQueue;

ArrayQueue *
createArrayQueue(void);

void
freeArrayQueue(ArrayQueue *queue);

QueueStatus
enqueueArray(ArrayQueue *q, Element val);

QueueStatus
dequeueArray(ArrayQueue *q, Element *element);

unsigned long
getArraySize(const ArrayQueue *q);

#endif //LAB5_SRC_C_ARRAYQUEUE_H
