#include "../include/Table.h"

static Table table;

Table *
tableGet(void)
{
    return &table;
}

#define GET_LENGTH(var, file) \
do                                  \
{                                   \
    fseek(file, 0L, SEEK_END);          \
    var = ftell(file) / sizeof(Car);    \
    rewind(file);                       \
} while(0)

ExitCode
tableReadFile(char *path)
{
    ExitCode code = OK;

    if (table.length != 0)
    {
        for (int i = 0; i < table.length; i++)
            tableDeleteCar(0);
        // TODO: check if won't work
    }
    table.length = 0;

    FILE *file = fopen(path, "rb");

    if (file == NULL)
        return ERR_FILE;

    GET_LENGTH(table.length, file);

    size_t read = 0;
    if (table.length < 0 OR table.length > MAX_TABLE_LENGTH)
        code = ERR_FILE;
    else
        read = fread(&table.values, sizeof(Car), table.length, file);

    if (read != table.length)
        code = ERR_FILE;

    fclose(file);
    return code;
}

ExitCode
tableSave(char *path)
{
    ExitCode code = OK;
    FILE *file = fopen(path, "wb");

    if (file == NULL)
        return ERR_FILE;

    size_t written = fwrite(&table.values, sizeof(Car), table.length, file);

    if (written != table.length)
        code = ERR_FILE;

    fclose(file);
    return code;
}

ExitCode
tableAddCar(Car car)
{
    if (table.length >= MAX_TABLE_LENGTH)
        return ERR_TABLE;

    table.values[table.length] = car;
    table.length++;
    return OK;
}

ExitCode
tableDeleteCar(size_t index)
{
    if (index >= table.length)
        return ERR_ARGS;

    if (table.length < 1)
        return ERR_TABLE;

    for (size_t i = index; i < table.length - 1; i++)
        table.values[i] = table.values[i + 1];

    table.length -= 1;
    table.values[table.length] = NULL_CAR;
    return OK;
}

int
key(const void *p1, const void *p2)
{
    const Car car1 = *((Car *) p1);
    const Car car2 = *((Car *) p2);

    if (car1.price < car2.price)
        return -1;
    else if (car1.price > car2.price)
        return 1;
    else
        return 0;
}

#include <time.h>

#define NANO_SEC(time) (time.tv_sec * 1000000000ULL + time.tv_nsec)

ExitCode
tableSort(long sortType, unsigned long *time)
{
    struct timespec start, end;

    SortFunc sort = getSort(sortType);
    if (sort == NULL)
        return ERR_ARGS;

    if (table.length)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        sort(table.values, table.length, sizeof(Car), key);
        clock_gettime(CLOCK_REALTIME, &end);

        *time = NANO_SEC(end) - NANO_SEC(start);
    }
    else
        return ERR_TABLE;

    return OK;
}

ExitCode
tableFindCars(unsigned long mileageParam)
{
    Table newTable = {0};
    for (unsigned long i = 0; i < table.length; i++)
    {
        if (NOT table.values[i].new AND table.values[i].FIND_FIELD <= mileageParam)
        {
            newTable.values[newTable.length] = table.values[i];
            newTable.length++;
        }
    }

    tablePrint(&newTable);

    return OK;
}

void
tablePrint(Table *table__)
{
    if (table__ == NULL)
        table__ = &table;

    if (table__->length < 1)
    {
        printf("Empty table\n");
        return;
    }

    printf(TABLE_HEADER);
    for (size_t i = 0; i < table__->length; i++)
    {
        printf("|%4lu", i);
        carPrint(table__->values[i]);
        printf("\n");
    }
}


