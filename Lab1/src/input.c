#include "input.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>
#include "utils/StringUtils.h"

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

typedef enum MODES {
    VALUE,
    EXPONENT,
    POINT
} MODE;


int
count

ExitCode
convert(String rawNumber, Number* number)
{
    String valuePart = "";
    char* valuePartPtr = valuePart;
    int pointPosition = 0;
    String exponentPart = "";
    char signPart = 0;

    printf("%s\n", rawNumber);

    if (*rawNumber == '-')
        signPart = 1, shiftLeft(rawNumber, 1);
    else if (*rawNumber == '+')
        shiftLeft(rawNumber, 1);
    else if (NOT isdigit(*rawNumber))
        return ERROR;

    stripLeft(rawNumber, '0');

    printf("%s\n", rawNumber);

    // TODO: strip, shift

    char* pointPointer = strchr(rawNumber, '.');
    if (pointPointer != NULL)
        pointPosition =

    return OK;
}

