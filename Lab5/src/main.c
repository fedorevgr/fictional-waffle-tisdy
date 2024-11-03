#include "Service.h"

typedef enum Modes_
{
    ARRAY,
    LIST,
    EXPERIMENT
} Modes;

int
main(void)
{
    bool verbose = true, showAddresses = false;
    ResultData results;
    size_t ticks = simulateListQueue(verbose, showAddresses, &results);
    printf("%lu\n", ticks);
    return 0;
}
