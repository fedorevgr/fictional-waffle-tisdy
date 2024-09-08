#include "StringUtils.h"


ExitCode
shiftLeft(String string, int shift)
{
    for (; *(string + shift); string++)
        *string = *(string + shift);

    for (; *string; string++)
        *string = '\0';

    return OK;
}

ExitCode
delete(String string, int position)
{
    string += position;
    for (; *(string + 1); string++)
        *string = *(string + 1);

    *string = '\0';

    return OK;
}

int
stripLeft(String string, char c)
{
    char* startString = string;
    int passedCounter = 0;

    for (; *string == c; string++, passedCounter++);

    for (; *string; startString++, string++)
        *startString = *string;

    for (; *startString; startString++)
        *startString = '\0';

    return passedCounter;
}

