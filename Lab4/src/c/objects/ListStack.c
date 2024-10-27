#include "objects/ListStack.h"

ListStack *
listStackCreate(void)
{
    return listCreate();
}

void
listStackDestroy(ListStack *stack)
{
    listDestroy(stack);
}

ExitCode
lStackPush(ListStack *stack, StackElement value)
{
    return listAppend(stack, value);
}

ExitCode
lStackPop(ListStack *stack, StackElement **poppedAddress)
{
    return listPop(stack, poppedAddress);
}

#include <assert.h>
StackElement *
listStackGet(ListStack *stack, size_t index) {
    assert(0);
}

