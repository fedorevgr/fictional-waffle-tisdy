#ifndef LAB2_TABLE_H
#define LAB2_TABLE_H

#include <string.h>
#include <stdio.h>

#include "Car.h"
#include "common/ExitCodes.h"
#include "common/Macros.h"

#define MAX_TABLE_LENGTH 100

typedef struct
{
    Car values[MAX_TABLE_LENGTH];
    int length;
} Table;

Table *
tableGet(void);
ExitCode
tableAddCar(Car);
ExitCode
tableDeleteCar(size_t);
ExitCode
tableSort(int);
ExitCode
tableFindCars(unsigned long);
void
tablePrint(Table *);
ExitCode
tableReadFile(char *path);
ExitCode
tableSave(char *path);

#endif //LAB2_TABLE_H
