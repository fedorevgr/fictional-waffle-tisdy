#ifndef LAB4_SRC_C_OBJECTS_STACK_H
#define LAB4_SRC_C_OBJECTS_STACK_H

#include "Codes.h"

#include "primitives/StackElement.h"
#include "primitives/Array.h"

typedef enum StackType_
{
    FROM_START = 's',
    FROM_END = 'e'
} StackType;

typedef struct Stack_
{
    size_t cursor;
    size_t reversedCursor;
    Array *space;
} Stack;

Stack *
stackCreate(size_t size);
void stackDestroy(Stack *);

ExitCode stackPush(Stack *, StackElement, StackType);
ExitCode
stackPop(Stack *, StackType, StackElement **poppedAddress);

StackElement *
stackGet(Stack *stack, size_t index, StackType from);

#endif //LAB4_SRC_C_OBJECTS_STACK_H
