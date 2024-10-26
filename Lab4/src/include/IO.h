//
// Created by Fedor Evgr on 22/10/2024.
//

#ifndef LAB4_SRC_C_IO_H
#define LAB4_SRC_C_IO_H

#include "objects/ListStack.h"
#include "objects/Stack.h"
#include "primitives/PrimitiveInput.h"

typedef enum StackOptions
{
    PUSH = 'p',
    POP = 'd',
    QUIT = 'q',
    SHOW = 's'
} StackOption;

StackOption
inputStackAction(void);

StackType
inputStackType(void);

void
stackPrint(Stack *stack);

void
listStackPrint(ListStack *stack);

#endif //LAB4_SRC_C_IO_H
