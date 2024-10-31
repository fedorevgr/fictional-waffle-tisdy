
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
} ListQueue;

ListQueue *
createListQueue(void);

void
freeListQueue(ListQueue *q);

ExitCode
enqueueList(ListQueue *q, Element value);

Element
dequeueList(ListQueue *q);

#endif //LAB5_SRC_C_LISTQUEUE_H
