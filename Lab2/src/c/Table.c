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
        table.length = 0;
    }

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
    assert(index >= 0);
    assert(index < table.length);

    if (table.length < 1)
        return ERR_TABLE;

    for (size_t i = index; index < table.length - 1; i++)
        table.values[i] = table.values[i + 1];

    table.length -= 1;
    table.values[table.length] = NULL_CAR;
    return OK;
}

// TODO:
//  ExitCode sort(int sortType);

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


