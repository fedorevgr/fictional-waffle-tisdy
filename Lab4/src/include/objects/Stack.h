#ifndef LAB4_SRC_C_OBJECTS_STACK_H
#define LAB4_SRC_C_OBJECTS_STACK_H

#include "Codes.h"

#include "primitives/StackElement.h"
#include "primitives/Array.h"

#ifndef STACK_SPACE
    #define STACK_SPACE    1000
#endif

typedef struct Stack_
{
    size_t cursor;
    size_t reversedCursor;
    Array *space;
} Stack;

Stack *stackCreate(void);
void stackDestroy(Stack *);

ExitCode stackPush(Stack *, StackElement);
ExitCode stackPop(Stack *);

#endif //LAB4_SRC_C_OBJECTS_STACK_H
