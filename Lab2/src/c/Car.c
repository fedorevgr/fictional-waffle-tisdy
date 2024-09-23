#include "../include/Car.h"
#include "ctype.h"

ExitCode
inputColour__(char *buffer)
{
    ExitCode code = inputString(buffer, WIDTH_CLR);

    for (int i = 0; i < WIDTH_CLR AND code == OK; i++)
    {
        if (NOT(
            ('a' <= buffer[i] AND buffer[i] <= 'f')
                OR
                ('0' <= buffer[i] AND buffer[i] <= '9')
        )
            )
            code = ERR_INPUT;
    }

    return code;
}

void
inputBoolean(bool *buffer)
{
    ExitCode code;
    char tmp[2];

    do
    {
        code = inputString(tmp, 1);

        if (code == OK)
        {
            if (tmp[0] == 'y')
                *buffer = 1;
            else if (tmp[0] == 'n')
                *buffer = 0;
            else
                code = ERR_INPUT;
        }
        else
            printf("AGAIN\n");
    }
    while (code != OK);
}

void
inputNew(Car *car)
{
    unsigned long buffer;
    ExitCode code;
    do
    {
        printf(PROMPT_NEW_GUARANTEE);
        code = inputUnsignedLong(&buffer);
    }
    while (code != OK);

    car->state.new.guarantee = buffer;
}

void
inputOld(Car *car)
{
    long buffer;
    ExitCode code;
    do
    {
        printf(PROMPT_OLD_YEAR);
        code = inputLong(&buffer);
    }
    while (code != OK);

    car->state.old.yearProd = (int) buffer;

    unsigned long ulBuffer;
    do
    {
        printf(PROMPT_OLD_MILEAGE);
        code = inputUnsignedLong(&ulBuffer);
    }
    while (code != OK);

    car->state.old.mileage = ulBuffer;

    do
    {
        printf(PROMPT_OLD_OWNERS);
        code = inputUnsignedLong(&ulBuffer);
    }
    while (code != OK);

    car->state.old.owners = ulBuffer;

    do
    {
        printf(PROMPT_OLD_REPAIR);
        code = inputUnsignedLong(&ulBuffer);
    }
    while (code != OK);

    car->state.old.repairs = ulBuffer;
}

ExitCode
inputCar(void)
{
    ExitCode code;
    Car newCar = NULL_CAR;

    do
    {
        printf(PROMPT_MANUFACTURER);
        code = inputString(newCar.manufacturer, MAX_STRING_LENGTH);
    }
    while (code != OK);

    do
    {
        printf(PROMPT_PRICE);
        code = inputUnsignedLong(&(newCar.price));
    }
    while (code != OK);

    do
    {
        printf(PROMPT_COUNTRY);
        code = inputString(newCar.country, 2);

        if (code)
        {
            if (NOT
                (
                    (
                        ('a' <= newCar.country[0] AND newCar.country[0] <= 'z')
                            OR
                            ('A' <= newCar.country[0] AND newCar.country[0] <= 'Z')
                    )
                        AND
                        (
                            ('a' <= newCar.country[1] AND newCar.country[1] <= 'z')
                                OR
                                ('A' <= newCar.country[1] AND newCar.country[1] <= 'Z')
                        )
                )
                )
                code = ERR_INPUT;
        }
    }
    while (code != OK);

    newCar.country[0] = (char) tolower(newCar.country[0]);
    newCar.country[1] = (char) tolower(newCar.country[1]);

    if (strncmp(newCar.country, "ru", 2) == 0)
    {
        printf(PROMPT_SERVICE);
        inputBoolean(&(newCar.dealerService));
    }

    do
    {
        printf(PROMPT_COLOUR);
        code = inputColour__(newCar.colour);
    }
    while (code != OK);

    printf(PROMPT_NEW);
    inputBoolean(&(newCar.new));

    if (newCar.new)
        inputNew(&newCar);
    else
        inputOld(&newCar);

    return OK;
}

const char *
getSpaces(char *str, int amount);

void
carPrint(Car car)
{
    char tmp[WIDTH_NAME + 1] = "";
    printf("| %s%s |", car.manufacturer, getSpaces(tmp, WIDTH_NAME - strlen(car.manufacturer)));
    printf(" %c%c-%s |", car.country[0], car.country[1], (car.dealerService) ? "YES" : "NO ");

    // char tmp2[WIDTH_PRICE + 1] = "";
    printf(" %10lu |", car.price); // TODO: switch %s

    printf(" %c%c%c%c%c%c |", car.colour[0], car.colour[1], car.colour[2], car.colour[3], car.colour[4], car.colour[5]);

    if (car.new)
    {
        printf(" %9du |", car.state.new.guarantee);
        printf("          |       |       |");
    }
    else
    {
        printf(" %9d |", car.state.old.yearProd);
        printf(" %8lu |", car.state.old.mileage);
        printf(" %4du |", car.state.old.owners);
        printf(" %4du |", car.state.old.repairs);
    }
}
