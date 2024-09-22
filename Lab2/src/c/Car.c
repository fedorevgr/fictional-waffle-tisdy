#include "../include/Car.h"

const char *getSpaces(char *str, int amount)
{
    for (int i = 0; i < amount; i++)
        str[i] = ' ';
    return str;
}

int getIntLength(unsigned long number)
{
    int length = 0;
    while (number)
    {
        number %= 10;
        length++;
    }
    return length;
}

void carPrint(Car car)
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
        printf(" %8lu |", car.state.old.run);
        printf(" %4du |", car.state.old.owners);
        printf(" %4du |", car.state.old.repairs);
    }
}
