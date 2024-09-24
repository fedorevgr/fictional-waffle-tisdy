//
// Created by Fedor Evgr on 20/09/2024.
//

#include "../../include/IO/input.h"

ExitCode
inputString(char *buffer, int limit)
{
    char *input_buffer = malloc(limit + 2);
    char *tmp = fgets(input_buffer, limit + 2, stdin);

    if (tmp[limit] != '\n' && tmp[limit] != '\0')
    {
        free(input_buffer);
        return ERR_INPUT;
    }

    char *c = strrchr(tmp, '\n');

    if (c == NULL)
    {
        free(input_buffer);
        printf("E: String out of bounds\n");
        return ERR_INPUT;
    }
    else
        *c = '\0';

    strcpy(buffer, input_buffer);
    free(input_buffer);

    if (strlen(buffer) == 0)
    {
        printf("E: Zero length string\n");
        return ERR_INPUT;
    }

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