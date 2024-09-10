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
    char *startString = string;
    int passedCounter = 0;

    for (; *string == c; string++, passedCounter++);

    for (; *string; startString++, string++)
        *startString = *string;

    for (; *startString; startString++)
        *startString = '\0';

    return passedCounter;
}

int
stripRight( const char *stringStart, char *stringEnd, char c)
{
    int i = 0;
    stringEnd--;
    for (; stringStart <= stringEnd AND *stringEnd == c; i++, stringEnd--)
        *stringEnd = '\0';
    return i;
}

