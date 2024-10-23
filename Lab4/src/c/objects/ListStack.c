#include "objects/ListStack.h"

ListStack *
listStackCreate(void)
{
    ListStack *listStack = malloc(sizeof(ListStack));

    if (listStack)
    {
        listStack->first = NULL;
    }

    return listStack;
}

void
listStackDestroy(ListStack *stack)
{

}

ExitCode
lStackPush(ListStack *stack, StackElement value)
{}

ExitCode
lStackPop(ListStack *stack)
{}

StackElement *
listStackGet(ListStack *stack, size_t index) {}

