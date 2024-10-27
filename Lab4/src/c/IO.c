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
}

void
listStackPrint(ListStack *stack)
{
    printf("List stack\n");
    printf("#   | Value   | Address\n");

    Node *node = stack->first;

    for (size_t i = 0; node; i++, node = node->next)
        printf("%3lu | %6g | %p\n", i + 1, node->value, node);
}


