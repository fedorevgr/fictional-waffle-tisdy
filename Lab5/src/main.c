#include "Service.h"

int
main(void)
{
    size_t ticks = simulateArrayQueue();
    printf("%lu\n", ticks);
    return 0;
}
