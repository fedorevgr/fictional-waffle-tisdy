#include "IterCounters.h"

int counter = 0;

void reset_(void)
{
    counter = 0;
}

int counterGet(void)
{
    int res = counter;
    reset_();
    return res;
}

void counterInc(void)
{
    counter += 1;
}
