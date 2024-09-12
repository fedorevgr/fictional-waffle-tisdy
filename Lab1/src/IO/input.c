#include "input.h"
#include <ctype.h>
#include <string.h>
#include "Validation//StringUtils.h"
#include <stdlib.h>

ExitCode
enter_(char *buffer)
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

#define EXP_ERROR (-10000000)
int
getExponent(char *expPointer)
{
    expPointer++;
    char *checkPointer;
    int result = (int) strtol(expPointer, &checkPointer, 10);
    return (checkPointer == expPointer + strlen(expPointer)) ? result : EXP_ERROR;
}

int
utilCountExponent(String string)
{
    int exponent = 0;
    for (; isdigit(*string); string++, exponent++);
    return exponent;
}


ExitCode
convert_(String rawNumber, Number *number)
{
    char sign = 0;
    if (*rawNumber == '-')
        sign = 1, shiftLeft(rawNumber, 1);
    else if (*rawNumber == '+')
        shiftLeft(rawNumber, 1);
    stripLeft(rawNumber, '0');

    int exponent = utilCountExponent(rawNumber);

    char *pointPointer = strchr(rawNumber, '.');
    char *exponentPointer = strpbrk(rawNumber, "eE");

    char *forCounterLeft = pointPointer;
    char *forCounterRight = (exponentPointer != NULL) ? exponentPointer : (rawNumber + strlen(rawNumber));

    if (pointPointer != NULL)
        delete(rawNumber, (int) (pointPointer - rawNumber));
    exponent -= stripLeft(rawNumber, '0');

    char *numberEndPointer = rawNumber + strlen(rawNumber);

    exponentPointer = strpbrk(rawNumber, "eE");
    if (exponentPointer != NULL)
    {
        int readExp = getExponent(exponentPointer);

        if (readExp == EXP_ERROR)
            return ERROR_VALIDATION;

        exponent += readExp;
        numberEndPointer = exponentPointer;
    }

    int lengthShortening = stripRight(rawNumber, numberEndPointer, '0'); // 10000000000000000000000000000000000999999

    if (pointPointer != NULL AND forCounterLeft + LENGTH_LIMIT((*number)) + 1 < forCounterRight)
        return ERROR_LIMITS;

    numberEndPointer -= lengthShortening;

    if (rawNumber == numberEndPointer)
        *rawNumber = '0', numberEndPointer++;

    if (rawNumber + LENGTH_LIMIT((*number)) < numberEndPointer)
        return ERROR_LIMITS;

    if (exponent > EXPONENT_LIMIT)
        return ERROR_LIMITS;

    setSign(number, sign);
    setValue(number, rawNumber, numberEndPointer);
    setExponent(number, exponent);

    return OK;
}

ExitCode
input(Number *number)
{
    char bufferString[MAX_STRING_LENGTH] = "";

    ExitCode exitCode = enter_(bufferString);

    if (exitCode != OK)
        return exitCode;

    return convert_(bufferString, number);
}

