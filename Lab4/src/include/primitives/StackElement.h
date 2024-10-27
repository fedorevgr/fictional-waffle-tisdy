//
// Created by Fedor Evgr on 22/10/2024.
//

#ifndef LAB4_SRC_INCLUDE_PRIMITIVES_STACKELEMENT_H
#define LAB4_SRC_INCLUDE_PRIMITIVES_STACKELEMENT_H

typedef double StackElement;

#define POPPED_MAX_LENGTH 1000
typedef struct Popped_
{
    unsigned long length;
    StackElement *values[POPPED_MAX_LENGTH];
}
PoppedList;

#endif //LAB4_SRC_INCLUDE_PRIMITIVES_STACKELEMENT_H
