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
    ExitCode exitCode;
    StackOption option;
    StackType type;

    StackElement buffer;

    stack = stackCreate();

    do
    {
        exitCode = OK;
        option = inputStackAction();
        
        if (option == PUSH || option == POP)
            type = inputStackType();

        switch (option)
        {
            case PUSH:
                if (inputDouble(&buffer) == INPUT_OK)
                    exitCode = stackPush(stack, buffer, type);
                else
                    printf("Illegal input\n");

                if (exitCode)
                    printf("Error: OVERFLOW\n");
                break;
            case POP:
                exitCode = stackPop(stack, type);
                if (exitCode)
                    printf("Error: POP FROM EMPTY\n");
                break;
            case QUIT:break;
            case SHOW:
                stackPrint(stack);
                break;
        }
    }
    while (option != QUIT);
    printf("Quiting");

    stackDestroy(stack);
}

void
serviceListStack(void)
{
    ListStack *listStack;
    ExitCode exitCode = OK;
}

void
serviceExperiment(void)
{

}
