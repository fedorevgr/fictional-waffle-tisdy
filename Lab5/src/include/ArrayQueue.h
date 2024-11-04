#ifndef LAB5_SRC_C_ARRAYQUEUE_H
#define LAB5_SRC_C_ARRAYQUEUE_H

#include "QueueElement.h"
#include "ExitCodes.h"

#define MAX_SIZE 5050

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

#endif //LAB5_SRC_C_ARRAYQUEUE_H
