#include "objects/Stack.h"

Stack *
stackCreate(size_t size)
{
    Stack *stack;

    stack = malloc(sizeof(Stack));

    if (stack)
    {
        stack->cursor = 0;
        stack->reversedCursor = size - 1;
        stack->space = arrayCreate(size);

        if (!stack->space)
        {
            free(stack);
            stack = NULL;
        }
    }

    return stack;
}

void
stackDestroy(Stack *stack)
{
    free(stack->space);
    free(stack);
}

static ExitCode
stackPushStart_(Stack *stack, StackElement value);

static ExitCode
stackPushEnd_(Stack *stack, StackElement value);

static ExitCode
stackPopStart_(Stack *stack, StackElement **poppedAddress);

static ExitCode
stackPopEnd_(Stack *stack, StackElement **poppedAddress);

static StackElement *
stackStartGet_(Stack *stack, size_t index);

static StackElement *
stackEndGet_(Stack *stack, size_t index);

StackElement *
stackGet(Stack *stack, size_t index, StackType from)
{
    return (from == FROM_START) ? stackStartGet_(stack, index) : stackEndGet_(stack, index);
}

ExitCode
stackPush(Stack *stack, StackElement value, StackType to)
{
    return (to == FROM_START) ? stackPushStart_(stack, value) : stackPushEnd_(stack, value);
}

ExitCode
stackPop(Stack *stack, StackType from, StackElement **poppedAddress)
{
    return (from == FROM_START) ? stackPopStart_(stack, poppedAddress) : stackPopEnd_(stack, poppedAddress);
}

static ExitCode
stackPushStart_(Stack *stack, StackElement value)
{
    if (stack->cursor > stack->reversedCursor)
        return ERROR_STACK_OVERFLOW;

    stack->space->elements[stack->cursor] = value;
    stack->cursor += 1;
    return OK;
}

static ExitCode
stackPushEnd_(Stack *stack, StackElement value)
{
    if (stack->cursor > stack->reversedCursor)
        return ERROR_STACK_OVERFLOW;

    stack->space->elements[stack->reversedCursor] = value;
    stack->reversedCursor -= 1;
    return OK;
}

static ExitCode
stackPopStart_(Stack *stack, StackElement **poppedAddress)
{
    if (stack->cursor == 0)
    {
        if (poppedAddress)
            *poppedAddress = NULL;
        return ERROR_STACK_EMPTY;
    }

    stack->cursor -= 1;
    if (poppedAddress)
        *poppedAddress = stack->space->elements + stack->cursor;
    return OK;
}

static ExitCode
stackPopEnd_(Stack *stack, StackElement **poppedAddress)
{
    if (stack->reversedCursor + 1 == stack->space->length)
    {
        if (poppedAddress)
            *poppedAddress = NULL;
        return ERROR_STACK_EMPTY;
    }

    stack->reversedCursor += 1;
    if (poppedAddress)
        *poppedAddress = stack->space->elements + stack->reversedCursor;
    return OK;
}

static StackElement *
stackStartGet_(Stack *stack, size_t index)
{
    if (stack->cursor <= index)
        return NULL;

    return stack->space->elements + index;
}

static StackElement *
stackEndGet_(Stack *stack, size_t index)
{
    size_t normalCursor = stack->space->length - stack->reversedCursor - 1;
    if (normalCursor <= index)
        return NULL;

    return stack->space->elements + stack->space->length - 1 - index;
}
