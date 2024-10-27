#ifndef LAB4_SRC_C_PRIMITIVES_LIST_H
#define LAB4_SRC_C_PRIMITIVES_LIST_H

#include "primitives/StackElement.h"
#include "Codes.h"
#include <stdlib.h>

typedef struct Node_ Node;

typedef struct Node_
{
    StackElement value;
    Node *next;
} Node;

typedef struct List_
{
    Node *first;
} List;

List *
listCreate(void);

void
listDestroy(List *);

ExitCode
listAppend(List *, StackElement);

ExitCode
listPop(List *, StackElement **poppedAddress);

StackElement *
listGet(List *, size_t);

#endif //LAB4_SRC_C_PRIMITIVES_LIST_H
