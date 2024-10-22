#ifndef LAB4_SRC_C_OBJECTS_LISTSTACK_H
#define LAB4_SRC_C_OBJECTS_LISTSTACK_H

#include "primitives/StackElement.h"
#include "primitives/List.h"

typedef List ListStack;

ListStack *listStackCreate(void);
void *listStackDestroy(ListStack *);

ExitCode lStackPush(ListStack *, StackElement);
ExitCode lStackPop(ListStack *);

#endif //LAB4_SRC_C_OBJECTS_LISTSTACK_H
