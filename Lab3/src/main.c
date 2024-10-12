#include "simple/PrimitiveInput.h"
#include "Codes.h"
#include <stdio.h>
#include <stdbool.h>
#include "Service.h"

void
pooling(void);

int
main(void)
{
    pooling();
    return 0;
}

#define POOL  "\n\n\n" \
    "q - quit\n" \
    "m - multiply\n" \
    "s - run time measurements\n" \

typedef enum
{
    POOL_ERROR,
    QUIT = 'q',
    MULTIPLY = 'm',
    STATS = 's'
} Pool;

Pool
inputPool(void)
{
    printf(POOL);
    Pool res = POOL_ERROR;
    char buffer[MAX_BUFFER_LENGTH + 1] = "";

    printf("Input option: ");
    InputError code = inputString(buffer);

    if (code == INPUT_OK)
        res = (Pool) buffer[0];

    return res;
}

void
pooling(void)
{
    bool end = false;
    do
    {
        switch (inputPool())
        {
            case POOL_ERROR:printf("Error input\n");
                break;
            case QUIT:printf("Quiting...\n");
                end = true;
                break;
            case MULTIPLY:serviceMultiply();
                break;
            case STATS:serviceStats();
                break;
            default:
                printf("Illegal option\n");
        }
    }
    while (!end);
}
