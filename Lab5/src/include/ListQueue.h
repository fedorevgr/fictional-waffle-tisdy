
#ifndef LAB5_SRC_C_LISTQUEUE_H
#define LAB5_SRC_C_LISTQUEUE_H

#include "QueueElement.h"
#include "ExitCodes.h"

typedef struct Node {
    Element data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} ListQueue;

ListQueue *
createListQueue(void);

void
freeListQueue(ListQueue *q);

QueueStatus
enqueueList(ListQueue *q, Element value);

QueueStatus
dequeueList(ListQueue *q, Element *element);

unsigned long
getListSize(const ListQueue *q);

#endif //LAB5_SRC_C_LISTQUEUE_H
