//
// Created by Fedor Evgr on 20/09/2024.
//

#include "../../include/IO/input.h"

ExitCode
inputString(char *buffer, int limit)
{
    char *tmp = fgets(buffer, limit + 1, stdin);

    tmp[limit] = '\0';
    char *c = strrchr(tmp, '\n');

    if (c == NULL)
        return ERR_INPUT;
    else
        *c = '\n';

    return OK;
}

#define MAX_INT_LENGTH 10
ExitCode
inputLong(long *buffer)
{
    char string[MAX_INT_LENGTH] = "";
    ExitCode code = inputString(string, MAX_INT_LENGTH);

    if (code != OK)
        return ERR_INPUT;

    char *end;
    *buffer = strtol(string, &end, 10);

    if (string + strlen(string) != end)
        return ERR_INPUT;

    return OK;
}

ExitCode
inputUnsignedLong(unsigned long *buffer)
{
    char string[MAX_INT_LENGTH] = "";
    ExitCode code = inputString(string, MAX_INT_LENGTH);

    if (code != OK)
        return ERR_INPUT;

    char *end;
    *buffer = strtoul(string, &end, 10);

    if (string + strlen(string) != end)
        return ERR_INPUT;

    return OK;
}