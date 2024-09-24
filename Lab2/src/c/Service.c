//
// Created by Fedor Evgr on 24/09/2024.
//

#include "../include/Service.h"

void
iPrintTable(void)
{
    tablePrint(NULL);
}

void
iAddCar(void)
{
    Car car = NULL_CAR;
    carInput(&car);

    if (tableAddCar(car) != OK)
    {
        printf("Error adding car\n");
    }
}

void
iDeleteCar(void)
{
    size_t index;
    printf("Input index: ");
    ExitCode code = inputUnsignedLong(&index);

    if (code)
    {
        printf("Illegal input\n");
        return;
    }

    code = tableDeleteCar(index);

    if (code)
    {
        printf("Unable to delete\n");
        return;
    }

}

void
iSortTable(void)
{
    unsigned long algorithm;
    printf(SORT_INFO);
    printf("Enter enter sort algorithm: ");
    ExitCode code = inputUnsignedLong(&algorithm);

    if (code)
    {
        printf("Illegal input\n");
        return;
    }

    if (algorithm == 1)
        // Todo: sort selection
        assert(0);
    else if (algorithm == 2)
        assert(0);
    else
        printf("Illegal option\n");
}

void
iFindFields(void)
{
    unsigned long mileage;

    printf("Enter mileage to find: ");
    ExitCode code = inputUnsignedLong(&mileage);
    if (code)
    {
        printf("Incorrect mileage\n");
        return;
    }

    tableFindCars(mileage);
}

void
iRead(void)
{
    char filename[MAX_STRING_LENGTH] = "";

    printf("Enter table filename: ");
    ExitCode code = inputString(filename, MAX_STRING_LENGTH);

    if (code)
    {
        printf("String input error\n");
        return;
    }
    code = tableReadFile(filename);
    if (code)
        printf("Error file\n");
}

void
iSave(void)
{
    char filename[MAX_STRING_LENGTH] = "";

    printf("Enter filename: ");
    ExitCode code = inputString(filename, MAX_STRING_LENGTH);

    if (code)
    {
        printf("String input error\n");
        return;
    }
    code = tableSave(filename);
    if (code)
        printf("Error file\n");
}

void
iStats(void)
{

}