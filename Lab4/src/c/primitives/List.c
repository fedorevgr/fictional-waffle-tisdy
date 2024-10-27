#include "primitives/List.h"

List *
listCreate(void)
{
    List *list = malloc(sizeof(List));

    if (list)
        list->first = NULL;

    return list;
}

void
listDestroy(List *list)
{
    while (list->first)
        listPop(list, nullptr);
    free(list);
}

ExitCode
listAppend(List *list, StackElement element)
{
    Node *node, *newNode;

    newNode = malloc(sizeof(Node));
    if (!newNode)
        return ERROR_MEMORY;

    newNode->value = element;
    newNode->next = NULL;

    if ((node = list->first))
    {
        while (node->next)
            node = node->next;

        node->next = newNode;
    }
    else
        list->first = newNode;

    return OK;
}

ExitCode
listPop(List *list, StackElement **poppedAddress)
{
    if (!list->first)
        return ERROR_STACK_EMPTY;

    Node *node = list->first, *prevNode = NULL;

    while (node->next)
    {
        prevNode = node;
        node = node->next;
    }

    if (prevNode)
        prevNode->next = NULL;
    else
        list->first = NULL;

    if (poppedAddress)
        *poppedAddress = &node->value;

    free(node);

    return OK;
}

#include <assert.h>
StackElement *
listGet(List *list, size_t index)
{
    assert(0);
}
