#include "Service.h"

typedef enum Modes_
{
    ARRAY = 'A',
    LIST = 'L',
    EXPERIMENT = 'E',
    CHANGE_VERBOSE = 'v',
    CHANGE_ADDRESS_DISPLAY = 'a'
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
