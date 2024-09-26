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
realisationSortTable(long algorithm)
{
    unsigned long time;
    ExitCode code = tableSort(algorithm, &time);

    if (code == ERR_TABLE)
    {
        printf("Can not sort empty table\n");
        return;
    }
    else if (code == ERR_ARGS)
    {
        printf("Illegal sort option\n");
        return;
    }
    printf("Sorting time: %lu\n", time);
}

void
realisationSortKeyTable(long algorithm)
{
    keyTableCreate();

    unsigned long time;
    ExitCode code = keyTableSort(algorithm, &time);

    if (code == ERR_TABLE)
    {
        printf("Can not sort empty table\n");
        return;
    }
    else if (code == ERR_ARGS)
    {
        printf("Illegal sort option\n");
        return;
    }

    KeyTable kt_ = *keyTableGet();
    Table t_ = *tableGet();

    printf(TABLE_HEADER);
    for (size_t i = 0; i < kt_.length; i++)
    {
        printf("|%4lu", i);
        carPrint(t_.values[kt_.keys[i].value]);
        printf("\n");
    }

    printf("Sorting time: %lu\n", time);
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

    long realisation;
    printf(REALISATION_INFO);
    printf("Enter realisation: ");
    code = inputLong(&realisation);

    if (code)
    {
        printf("Illegal input\n");
        return;
    }

    if (realisation == 1)
        realisationSortTable(algorithm);
    else if (realisation == 2)
        realisationSortKeyTable(algorithm);
    else
    {
        printf("Illegal realization option\n");
        return;
    }

}

void
iFindFields(void)
{
    ExitCode code;

    char name[MAX_STRING_LENGTH + 1] = "";

    printf("Enter manufacturer:\n");
    code = inputString(name, MAX_STRING_LENGTH);
    if (code)
    {
        printf("String input error\n");
        return;
    }

    unsigned long lowerPrice;
    printf("Enter lower price limit to find: ");
    code = inputUnsignedLong(&lowerPrice);
    if (code)
    {
        printf("Incorrect price\n");
        return;
    }

    unsigned long upperPrice;
    printf("Enter upper price limit to find: ");
    code = inputUnsignedLong(&upperPrice);
    if (code)
    {
        printf("Incorrect price\n");
        return;
    }

    tableFindCars(name, lowerPrice, upperPrice);
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

#include <time.h>

#define SELECTION 0
#define COMB      1
#define SELECTION_KEY 2
#define COMB_KEY      3

void
iStats(void)
{
    if (tableGet() -> length == 0)
    {
        ExitCode code = tableReadFile("big.foo");

        if (code != OK)
        {
            printf("Unable to run stats...\nFile big.foo error\n");
            return;
        }
    }
    keyTableCreate();

    unsigned long results[4];
    const time_t seed = time(NULL);

    srand(seed);
    shuffle(tableGet()->values, sizeof(Car), tableGet()->length);

    tableSort(1, results + SELECTION);

    srand(seed);
    shuffle(tableGet()->values, sizeof(Car), tableGet()->length);

    tableSort(2, results + COMB);

    srand(seed);
    shuffle(keyTableGet()->keys, sizeof(Key), keyTableGet()->length);

    keyTableSort(1, results + SELECTION_KEY);

    srand(seed);
    shuffle(keyTableGet()->keys, sizeof(Key), keyTableGet()->length);

    keyTableSort(2, results + COMB_KEY);

    printf(
        "|                               | Time (ns)          |\n"
        "| Table selection sort          | %18lu |\n"
        "| Table comb sort               | %18lu |\n"
        "| Key table selection sort      | %18lu |\n"
        "| Key table comb sort           | %18lu |\n",
        results[SELECTION], results[COMB], results[SELECTION_KEY], results[COMB_KEY]
    );
}

void
iKeyTablePrint(void)
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

    keyTableCreate();

    keyTablePrint(); // Todo: remove

    keyTableSort(algorithm, &time);

    keyTablePrint();
}

void
iFindByMileage(void)
{
    unsigned long mileage;

    printf("Enter mileage to find: ");
    ExitCode code = inputUnsignedLong(&mileage);
    if (code)
    {
        printf("Incorrect mileage\n");
        return;
    }

    Table t_ = *tableGet();

    printf("List of cars with required mileage\n\n");
    for (size_t i = 0; i < t_.length; i++)
    {
        if (
            NOT t_.values[i].new
            AND
            t_.values[i].state.old.mileage <= mileage
            )
        {
            printf("|%3lu", i);
            carPrint(t_.values[i]);
            printf("\n");
        }
    }
}