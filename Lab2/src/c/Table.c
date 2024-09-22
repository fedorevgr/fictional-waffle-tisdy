#include "../include/Table.h"


static Table table;

Table *tableGet(void)
{
	return &table;
}

ExitCode tableAddCar(Car car)
{
	if (table.length >= MAX_TABLE_LENGTH)
		return ERR_TABLE;

	table.values[table.length] = car;
    table.length++;
	return OK;
}

ExitCode tableDeleteCar(int index)
{
	assert(index >= 0);
	assert(index < table.length);

	if (table.length < 1)
		return ERR_TABLE;

	for (int i = index; index < table.length - 1; i++)
		table.values[i] = table.values[i + 1];

	table.length -= 1;
	table.values[table.length] = NULL_CAR;
	return OK;
}

// TODO:
//  ExitCode sort(int sortType);

ExitCode tableFindCars(char *key)
{
    printf(TABLE_HEADER);

    unsigned long count = 0;
    for (unsigned long i = 0; i < table.length; i++)
    {
        if (strncmp(table.values[i].FIND_FIELD, key, strlen(key)) == 0)
        {
            printf("|%4lu", i);
            carPrint(table.values[i]);
            printf("\n");
            count++;
        }
    }
    if (count == 0)
        printf("Empty table\n");

    return (count) ? OK : ERR_TABLE;
}




