#include "primitives/List.h"

List *
listCreate(void) {
    return NULL;
}

void
listDestroy(List *list)
{

}

ExitCode listAppend(List *list, StackElement element)
{
    return OK;
}

ExitCode listPop(List *list)
{
    return 0;
}

ExitCode listGet(List *list, size_t index, StackElement *)
{
    return 0;
}
