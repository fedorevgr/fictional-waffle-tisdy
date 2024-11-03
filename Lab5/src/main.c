#include "Service.h"

typedef enum Modes_
{
    ARRAY = 'A',
    LIST = 'L',
    EXPERIMENT = 'E',
    CHANGE_VERBOSE = 'v',
    CHANGE_ADDRESS_DISPLAY = 'a',
    EXIT = 'q'
} Mode;

char
getOption(void);

int
main(void)
{
    char mode;
    bool verbose = true, showAddresses = false;
    ResultData result;
    do
    {
        printf("Verbose: %d\nShow address: %d\n", verbose, showAddresses);

        mode = getOption();
        switch (mode)
        {
            case ARRAY:simulateArrayQueue(verbose, showAddresses, &result);
                break;
            case LIST:simulateListQueue(verbose, showAddresses, &result);
                break;
            case EXPERIMENT:serviceExperiment();
                break;
            case CHANGE_VERBOSE:verbose = !verbose;
                break;
            case CHANGE_ADDRESS_DISPLAY:showAddresses = !showAddresses;
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
               "- q - quit\n"
               "Option -> ");
        ec = inputString(tmp);
        if (ec == INPUT_OK && strpbrk(tmp, "ALEvaq") != tmp)
            ec = INPUT_E;

        if (ec)
            printf("Illegal option, Try again...\n");
    }
    while (ec != INPUT_OK);
    return tmp[0];
}
