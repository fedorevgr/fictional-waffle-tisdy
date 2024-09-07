#include "input.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>
#include "utils/StringUtils.h"
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
getExponent(char* expPointer)
{
    expPointer++;
    char* checkPointer;
    return (int) strtol(expPointer, &checkPointer, 10);
}


int
countExponent(String string)
{
    int exponent = 0;
    for (; isdigit(*string); string++, exponent++);
    return exponent;
}

// TODO: remove prints

ExitCode
convert(String rawNumber, Number* number)
{
    char* valuePointer;
    char* valueEndPointer;
    int pointPosition = 0;
    int exponent;
    String exponentPart = "";
    char sign = 0;
    char* numberEndPointer = rawNumber + strlen(rawNumber);

    printf("%s\n", rawNumber);

    if (*rawNumber == '-')
        sign = 1, shiftLeft(rawNumber, 1);
    else if (*rawNumber == '+')
        shiftLeft(rawNumber, 1);

    stripLeft(rawNumber, '0');

    exponent = countExponent(rawNumber);

    printf("%s %d\n", rawNumber, exponent);

    char* pointPointer = strchr(rawNumber, '.');
    if (pointPointer != NULL)
        delete(rawNumber, (int) (pointPointer - rawNumber));

    char* exponentPointer = strpbrk(rawNumber, "eE");
    if (exponentPointer != NULL)
        exponent += getExponent(exponentPointer);
    else
        valuePart = (char *) rawNumber;


    printf("%s %d\n", rawNumber, exponent);

    number->sign = sign;

    return OK;
}

