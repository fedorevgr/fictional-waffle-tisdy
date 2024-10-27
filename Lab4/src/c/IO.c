#include "IO.h"

#include <stdio.h>
#include <string.h>

size_t
inputSize(void)
{
    size_t number;
    InputError inputError;

    printf("Enter static stack size: ");
    do
    {
        inputError = inputUnsigned(&number);
        if (inputError)
            printf("Try again: ");
    }
    while (inputError);
    return number;
}


StackOption
inputStackAction(void)
{
    InputError inputStatus;
    char buffer[MAX_BUFFER_LENGTH + 2] = "";

    printf("Stack actions:\n p - Push\n d - Pop\n s - Show\n q - Quit\n");
    do
    {
        inputStatus = inputString(buffer);

        if (strlen(buffer) != 1 || strpbrk(buffer, "pdqs") == NULL)
            inputStatus = INPUT_E;

        if (inputStatus)
            printf("Retry: ");
    }
    while (inputStatus);

    return buffer[0];
}

StackType
inputStackType(void)
{
    InputError inputStatus;
    char buffer[MAX_BUFFER_LENGTH + 2] = "";

    printf("Enter stack (s(tart) | e(nd)): ");
    do
    {
        inputStatus = inputString(buffer);

        if (strlen(buffer) != 1 || !(buffer[0] == 's' || buffer[0] == 'e'))
            inputStatus = INPUT_E;

        if (inputStatus)
            printf("Illegal input, again: ");
    }
    while (inputStatus);

    return buffer[0];
}

void
stackPrint(Stack *stack)
{
    StackElement *fromStart, *fromEnd;
    printf("Array stack\n");
    printf("#   | Start  | Address        |  End   | Address \n");

    for (size_t i = 0;; i++)
    {
        fromStart = stackGet(stack, i, FROM_START);
        fromEnd = stackGet(stack, i, FROM_END);

        if (fromEnd == NULL && fromStart == NULL)
            break;

        printf("%3lu |", i + 1);

        if (fromStart)
            printf(" %6g | %p |", *fromStart, fromStart);
        else
            printf("        |                |");

        if (fromEnd)
            printf(" %6g | %p |", *fromEnd, fromEnd);
        else
            printf("        |                |");
        printf("\n");
    }
    printf("Memory status:\n  Used: %lu\n  Taken: %lu\n",
           sizeof(StackElement) * stack->cursor + sizeof(StackElement) * (stack->space->length - 1 - stack->reversedCursor) \
                + sizeof(size_t) * 2,
           sizeof(StackElement) * stack->space->length + sizeof(size_t) * 2
           );
}

void
listStackPrint(ListStack *stack)
{
    printf("List stack\n");
    printf("#   | Value   | Address\n");

    Node *node = stack->first;

    size_t length = 0;
    for (size_t i = 0; node; i++, node = node->next, length++)
        printf("%3lu | %6g | %p\n", i + 1, node->value, node);

    printf("Memory status:\n  Used: %lu\n  Taken: %lu\n",
           sizeof(Node) * (length + 1), sizeof(Node) * (length + 1)
    );
}

void
printFragmentation(PoppedList history)
{
    printf("Fragmentation (popped values):\n");

    if (history.length == 0)
    {
        printf("Nothing popped\n");
        return;
    }

    for (size_t i = 0; i < history.length; ++i)
        printf("  %p\n", history.values[i]);
}
