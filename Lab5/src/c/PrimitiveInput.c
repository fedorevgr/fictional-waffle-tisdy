#include "PrimitiveInput.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

InputError
inputString(char *buffer)
{
    char *tmp = fgets(buffer, MAX_BUFFER_LENGTH + 2, stdin);

    if (tmp[MAX_BUFFER_LENGTH] != '\n' && tmp[MAX_BUFFER_LENGTH] != '\0')
        return INPUT_E_LENGTH;

    tmp[MAX_BUFFER_LENGTH] = '\0';

    char *c = strrchr(tmp, '\n');
    if (!c)
        return INPUT_E;

    *c = '\0';

    if (c - buffer == 0)
        return INPUT_E_EMPTY;

    return INPUT_OK;
}

InputError
checkRead(const char *start, const char *end)
{
    if (strlen(start) == end - start)
        return INPUT_OK;
    return INPUT_E_READ;
}

InputError
strToDouble(char *str, double *n)
{
    char *readCheck = NULL;
    *n = strtod(str, &readCheck);

    return checkRead(str, readCheck);
}

InputError
strToUnsigned(char *str, unsigned long *n)
{
    char *readCheck = NULL;
    *n = strtoul(str, &readCheck, 10);

    return checkRead(str, readCheck);
}

InputError
strToSigned(char *str, long *n)
{
    char *readCheck = NULL;
    *n = strtol(str, &readCheck, 10);

    return checkRead(str, readCheck);
}

InputError
inputDouble(double *n)
{
    char buffer[MAX_BUFFER_LENGTH + 1] = "";

    InputError ec = inputString(buffer);

    if (ec == INPUT_OK)
    {
        ec = strToDouble(buffer, n);
    }
    return ec;
}

InputError
inputUnsigned(unsigned long *n)
{
    char buffer[MAX_BUFFER_LENGTH + 1] = "";

    InputError ec = inputString(buffer);

    if (ec == INPUT_OK)
    {
        ec = strToUnsigned(buffer, n);
    }
    return ec;
}

InputError
inputSigned(long *n)
{
    char buffer[MAX_BUFFER_LENGTH + 1] = "";

    InputError ec = inputString(buffer);

    if (ec == INPUT_OK)
    {
        ec = strToSigned(buffer, n);
    }
    return ec;
}
