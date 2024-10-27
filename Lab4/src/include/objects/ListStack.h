#ifndef LAB4_SRC_C_OBJECTS_LISTSTACK_H
#define LAB4_SRC_C_OBJECTS_LISTSTACK_H

#include "primitives/StackElement.h"
#include "primitives/List.h"

typedef List ListStack;

ListStack *listStackCreate(void);
void listStackDestroy(ListStack *stack);

ExitCode lStackPush(ListStack *, StackElement);
ExitCode
lStackPop(ListStack *, StackElement **poppedAddress);

StackElement *
listStackGet(ListStack *stack, size_t index);

#endif //LAB4_SRC_C_OBJECTS_LISTSTACK_H
