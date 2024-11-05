#include "Service.h"

typedef enum Modes_
{
    ARRAY = 'A',
    LIST = 'L',
    EXPERIMENT = 'E',
    CHANGE_VERBOSE = 'v',
    CHANGE_ADDRESS_DISPLAY = 'a',
    CHANGE_POOL_TIMER = 'p',
    CHANGE_SERVE_TIMER = 's',
    EXIT = 'q'
} Mode;

char
getOption(void);

size_t
changeValue(size_t oldValue);

// todo add change of basic values
int
main(void)
{
    char mode;
    bool verbose = true, showAddresses = false;
    size_t maxPoolTime = TIME_MAX_T1;
    size_t maxServeTime = TIME_MAX_T2;
    ResultData result;
    do
    {
        printf("Verbose: %d\nShow address: %d\n", verbose, showAddresses);
        printf("Request pull timer: %.1lf\nRequest serving time: %.1lf\n",
               (double) maxPoolTime / TIME_FACTOR,
               (double) maxServeTime / TIME_FACTOR);

        mode = getOption();
        switch (mode)
        {
            case ARRAY:simulateArrayQueue(maxPoolTime, maxServeTime, verbose, showAddresses, &result);
                break;
            case LIST:simulateListQueue(maxPoolTime, maxServeTime, verbose, showAddresses, &result);
                break;
            case EXPERIMENT:serviceExperiment();
                break;
            case CHANGE_VERBOSE:verbose = !verbose;
                break;
            case CHANGE_ADDRESS_DISPLAY:showAddresses = !showAddresses;
                break;
            case CHANGE_POOL_TIMER:maxPoolTime = changeValue(maxPoolTime);
                break;
            case CHANGE_SERVE_TIMER:maxServeTime = changeValue(maxServeTime);
                break;
            case EXIT:printf("Exiting...\n");
                break;
            default:printf("Illegal option\n");
        }
    }
    while (mode != EXIT);

    return 0;
}

#include "PrimitiveInput.h"
#include <string.h>

char
getOption(void)
{
    char tmp[MAX_BUFFER_LENGTH + 2] = "";
    InputError ec;
    do
    {
        printf("Enter option\n"
               "- A - run array model\n"
               "- L - run list model\n"
               "- E - run measurements\n"
               "- v - change verbose mode\n"
               "- a - change address display\n"
               "- p - change max pooling time\n"
               "- s - change max serve time\n"
               "- q - quit\n"
               "Option -> ");
        ec = inputString(tmp);
        if (ec == INPUT_OK && strpbrk(tmp, "ALEvaqps") != tmp)
            ec = INPUT_E;

        if (ec)
            printf("Illegal option, Try again...\n");
    }
    while (ec != INPUT_OK);
    printf("\n\n\n\n");
    return tmp[0];
}

#define TOLERANCE 0.1

size_t
changeValue(size_t oldValue)
{
    size_t newValue = oldValue;
    double newValueBuffer;

    printf("Enter new value (tolerance = %.1lf): ", TOLERANCE);
    InputError inputError = inputDouble(&newValueBuffer);

    if (inputError == INPUT_OK)
    {
        if (newValueBuffer < TOLERANCE)
            inputError = INPUT_E;
    }

    if (inputError == INPUT_OK)
        newValue = (size_t) (newValueBuffer * TIME_FACTOR);
    else
        printf("Illegal number\n");

    return newValue;
}