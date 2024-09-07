#include "input.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>
#include "Validation//StringUtils.h"
#include <stdlib.h>

ExitCode
enter(char *buffer)
{
    char tmp[MAX_STRING_LENGTH + 2] = "";
    char *readString = fgets(tmp, MAX_STRING_LENGTH + 2, stdin);

    if (readString == NULL)
        return ERROR;

    char *backChar = strrchr(tmp, '\n');
    if (backChar == NULL)
        return ERROR;
    *backChar = '\0';

    strcpy(buffer, tmp);

    return OK;
}

int
getExponent(char *expPointer)
{
    expPointer++;
    char *checkPointer;
    return (int) strtol(expPointer, &checkPointer, 10);
}

int
utilCountExponent(String string)
{
    int exponent = 0;
    for (; isdigit(*string); string++, exponent++);
    return exponent;
}


int
countExponent();


ExitCode
convert(String rawNumber, Number *number)
{
    char *numberEndPointer = rawNumber + strlen(rawNumber);

    char sign = 0;
    if (*rawNumber == '-')
        sign = 1, shiftLeft(rawNumber, 1);
    else if (*rawNumber == '+')
        shiftLeft(rawNumber, 1);
    stripLeft(rawNumber, '0');

    char *pointPointer = strchr(rawNumber, '.');
    if (pointPointer != NULL)
        delete(rawNumber, (int) (pointPointer - rawNumber));

    int exponent = utilCountExponent(rawNumber);
    char *exponentPointer = strpbrk(rawNumber, "eE");
    if (exponentPointer != NULL)
    {
        exponent += getExponent(exponentPointer);
        numberEndPointer = exponentPointer;
    }

    setSign(number, sign);
    setValue(number, rawNumber, numberEndPointer);
    setExponent(number, exponent);

    return OK;
}

