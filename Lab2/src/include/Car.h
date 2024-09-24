//
// Created by Fedor Evgr on 20/09/2024.
//

#ifndef LAB2_CAR_H
#define LAB2_CAR_H

#include "common/ExitCodes.h"
#include "common/Macros.h"
#include "IO/input.h"
#include "IO/output.h"
#include "IO/CarPrompts.h"

typedef struct
{
    unsigned int guarantee;
} StateNew;

typedef struct
{
    int yearProd;
    unsigned long mileage;
    unsigned int owners;
    unsigned int repairs;
} StateOld;

typedef union
{
    StateNew new;
    StateOld old;
} State;

#define COLOUR_LENGTH 6
#define COUNTRY_WIDTH 2

typedef struct
{
    char manufacturer[MAX_STRING_LENGTH + 1];
    char country[COUNTRY_WIDTH + 1];
    unsigned long price;
    char colour[COLOUR_LENGTH + 1];
    bool new;
    bool dealerService;
    State state;
}
    Car;

#define SORT_FIELD price
#define FIND_FIELD state.old.mileage

#define NULL_CAR  (Car) { 0 }

void
carPrint(Car);

ExitCode
carInput(Car *);

#endif //LAB2_CAR_H
