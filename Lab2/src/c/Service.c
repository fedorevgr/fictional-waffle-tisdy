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

    if (code == ERR_ARGS)
    {
        printf("Index out of range\n");
        return;
    }
    else if (code)
    {
        printf("Unable to delete\n");
        return;
    }

}

void
iSortTable(void)
{
    long algorithm;
    printf(SORT_INFO);
    printf("Enter enter sort algorithm: ");
    ExitCode code = inputLong(&algorithm);

    if (code)
    {
        printf("Illegal input\n");
        return;
    }
    unsigned long time;
    code = tableSort(algorithm, &time);

    if (code == ERR_TABLE)
        printf("Can not sort empty table\n");
    else if (code == ERR_ARGS)
        printf("Illegal sort option\n");
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