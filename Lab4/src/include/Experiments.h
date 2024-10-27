#ifndef LAB4_SRC_C_EXPERIMENTS_H
#define LAB4_SRC_C_EXPERIMENTS_H

#include "objects/Stack.h"
#include "objects/ListStack.h"

#define TIME_FMT "%9.1lf"

#define RUNS 1000

#define EXPERIMENTS 6

typedef enum EXP_ {
    PUSH_ARRAY_START,
    POP_ARRAY_START,
    PUSH_ARRAY_END,
    POP_ARRAY_END,
    PUSH_LIST,
    POP_LIST
} EXPERIMENT;

void
experiment(double *results, Stack *stack, ListStack *listStack);

double
measurePushStart(Stack *stack);

double
measurePopStart(Stack *stack);

double
measurePushEnd(Stack *stack);

double
measurePopEnd(Stack *stack);

double
measurePushList(ListStack *stack);

double
measurePopList(ListStack *stack);

#endif //LAB4_SRC_C_EXPERIMENTS_H
