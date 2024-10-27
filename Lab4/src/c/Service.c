#include "Service.h"
#include "objects/Stack.h"
#include "objects/ListStack.h"
#include "IO.h"
#include "Codes.h"

#include <stdio.h>
#include <assert.h>

void
serviceStack(void)
{
    Stack *stack;
    PoppedList popHistory = { 0 };
    ExitCode exitCode;
    StackOption option;
    StackType type;

    StackElement buffer;

    size_t stackSize = inputSize();
    stack = stackCreate(stackSize);

    do
    {
        exitCode = OK;
        option = inputStackAction();
        
        if (option == PUSH || option == POP)
            type = inputStackType();

        switch (option)
        {
            case PUSH:
                printf("Input value:");
                if (inputDouble(&buffer) == INPUT_OK)
                    exitCode = stackPush(stack, buffer, type);
                else
                    printf("Retry: ");

                if (exitCode)
                    printf("Error: OVERFLOW\n");
                break;
            case POP:
                exitCode = stackPop(stack, type, popHistory.values + popHistory.length);

                if (exitCode)
                    printf("Error: POP FROM EMPTY\n");
                else
                    popHistory.length += 1;
                break;
            case QUIT:break;
            case SHOW:
                stackPrint(stack);
                printFragmentation(popHistory);
                break;
        }
    }
    while (option != QUIT);
    printf("Quiting...\n");

    stackDestroy(stack);
}

void
serviceListStack(void)
{
    ListStack *listStack;
    ExitCode exitCode = OK;
    StackOption option;
    StackElement buffer;

    listStack = listStackCreate();

    PoppedList popHistory = { 0 };

    do
    {
        exitCode = OK;
        option = inputStackAction();

        switch (option)
        {
            case PUSH:
                printf("Input value:");
                if (inputDouble(&buffer) == INPUT_OK)
                    exitCode = lStackPush(listStack, buffer);
                else
                    printf("Retry: ");

                if (exitCode)
                    printf("Error: OVERFLOW\n");
                break;
            case POP:
                exitCode = lStackPop(listStack, popHistory.values + popHistory.length);
                if (exitCode)
                    printf("Error: POP FROM EMPTY\n");
                else
                    popHistory.length += 1;
                break;
            case QUIT:break;
            case SHOW:
                listStackPrint(listStack);
                printFragmentation(popHistory);
                break;
        }
    }
    while (option != QUIT);
    printf("Quiting");

    listStackDestroy(listStack);
}

#include "Experiments.h"

#define FAKE_STACK_LENGTH 1000

void
serviceExperiment(void)
{
    Stack *fakeStack = stackCreate(FAKE_STACK_LENGTH);
    for (int i = 0; i < FAKE_STACK_LENGTH; i++)
        stackPush(fakeStack, 1, FROM_START);
    stackDestroy(fakeStack);

    printf("Measurements:\n");

    double results[EXPERIMENTS] = { 0 };

    Stack *stack;
    ListStack *listStack;

    stack = stackCreate(RUNS);
    listStack = listStackCreate();

    experiment(results, stack, listStack);

    stackDestroy(stack);
    listStackDestroy(listStack);

    printf("     | Array     | Array End | %%     | List      | %%\n");
    printf("PUSH | " TIME_FMT " | " TIME_FMT " | %5.1lf | " TIME_FMT " | %5.1lf\n",
           results[PUSH_ARRAY_START],
           results[PUSH_ARRAY_END],
           (double) results[PUSH_ARRAY_END] / (double) results[PUSH_ARRAY_START] * 100 - 100,
           results[PUSH_LIST],
           (double) results[PUSH_LIST] / (double) results[PUSH_ARRAY_START] * 100 - 100
    );

    printf("POP  | " TIME_FMT " | " TIME_FMT " | %5.1lf | " TIME_FMT " | %5.1lf\n",
           results[POP_ARRAY_START],
           results[POP_ARRAY_END],
           (double) results[POP_ARRAY_END] / (double) results[POP_ARRAY_START] * 100 - 100,
           results[POP_LIST],
           (double) results[POP_LIST] / (double) results[POP_ARRAY_START] * 100 - 100
           );
    printf("Diff | %8.1lf%% | %8.1lf%% |       | %8.1lf%% |\n",
           results[POP_ARRAY_START] / results[PUSH_ARRAY_START] * 100 - 100,
           results[POP_ARRAY_END] / results[PUSH_ARRAY_END] * 100 - 100,
           results[POP_LIST] / results[PUSH_LIST] * 100 - 100
           );
}
