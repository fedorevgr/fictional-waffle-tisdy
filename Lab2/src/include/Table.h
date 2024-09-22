#ifndef LAB2_TABLE_H
#define LAB2_TABLE_H

#include <string.h>
#include <stdio.h>

#include "Car.h"
#include "common/ExitCodes.h"
#define MAX_TABLE_LENGTH 100

typedef struct
{
	Car values[MAX_TABLE_LENGTH];
	int length;
} Table;

Table *tableGet(void);
ExitCode tableAddCar(Car);
ExitCode tableDeleteCar(int);
ExitCode tableSort(int);
ExitCode tableFindCars(char *);

#endif //LAB2_TABLE_H
