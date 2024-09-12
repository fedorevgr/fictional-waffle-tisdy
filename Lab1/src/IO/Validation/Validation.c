#include "Validation.h"
#include <ctype.h>
#include <string.h>

// Mask [+-]?[0-9]+
ExitCode
validateInt(String string, const char *numberEnd, bool sign)
{
    if (numberEnd == NULL)
        numberEnd = string + strlen(string);

    if (sign)
    {
        if (*string == '-' OR *string == '+')
            string++;
        else if (NOT isdigit(*string))
            return ERROR_VALIDATION;
    }

    int counter = 0;
    for (; string < numberEnd; string++, counter++)
        if (NOT isdigit(*string))
            return ERROR_VALIDATION;

    if (counter == 0)
        return ERROR_VALIDATION;

    return OK;
}

ExitCode
specialFloat(String string, const char *numberEnd)
{
    if (*string == '-' OR *string == '+')
        string++;

    if (string == numberEnd)
        return OK;
    else
        return ERROR_VALIDATION;
}


ExitCode
validateReal(String string)
{
    ExitCode exitCode;

    char *numberEnd = string + strlen(string);
    char *pointPointer = strchr(string, '.');
    char *expPointer = strpbrk(string, "eE");

    if (pointPointer == NULL)
    {
        if (expPointer == NULL)
        {
            exitCode = validateInt(string, numberEnd, true);
        }
        else
        {
            exitCode = (
                validateInt(string, expPointer, true) == OK
                    AND
                    validateInt(expPointer + 1, numberEnd, true) == OK
            ) ? OK : ERROR_VALIDATION;
        }
    }
    else
    {
        if (expPointer == NULL)
        {
            exitCode = (
                (
                    validateInt(string, pointPointer, true) == OK
                        OR
                        specialFloat(string, pointPointer) == OK
                )
                    AND
                    validateInt(pointPointer + 1, numberEnd, false) == OK
            ) ? OK : ERROR_VALIDATION;
        }
        else
        {
            exitCode = (
                (
                    validateInt(string, pointPointer, true) == OK
                        OR
                        specialFloat(string, pointPointer) == OK
                )
                    AND
                    validateInt(pointPointer + 1, expPointer, false) == OK
                    AND
                    validateInt(expPointer + 1, numberEnd, true) == OK
            ) ? OK : ERROR_VALIDATION;
        }
    }
    return exitCode;
}


ExitCode
validateNumber(Number number)
{
    if (number.valueLength > LENGTH_LIMIT(number))
        return ERROR_VALIDATION;

    if (ABS(number.exponent) > EXPONENT_LIMIT)
        return ERROR_VALIDATION;

    return OK;
}
