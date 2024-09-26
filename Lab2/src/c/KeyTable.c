//
// Created by Fedor Evgr on 24/09/2024.
//

#include "../include/KeyTable.h"


static KeyTable keyTable = { 0 };

void
clearTable(void)
{
    keyTable = (KeyTable) { 0 };
}

KeyTable *
keyTableGet(void)
{
    return &keyTable;
}

void
keyTableCreate(void)
{
    clearTable();

    Table table = *tableGet();
    keyTable.length = table.length;
    for (size_t i = 0; i < table.length; i++)
    {
        keyTable.keys[i].value = i;
        keyTable.keys[i].key = table.values[i].price;
    }
}

void
keyTablePrint(void)
{
    if (keyTable.length == 0)
    {
        printf("Empty key table\n");
        return;
    }

    printf("| Key          | Index |\n");
    for (size_t i = 0; i < keyTable.length; i++)
    {
        printf("| %12lu | %5lu |\n", keyTable.keys[i].key, keyTable.keys[i].value);
    }
}

int
keyTableKey(const void *p1, const void *p2)
{
    Key k1 = *(Key *) p1;
    Key k2 = *(Key *) p2;

    if (k1.key > k2.key)
        return -1;
    else if (k1.key < k2.key)
        return 1;
    else
        return 0;
}

#include <time.h>

ExitCode
keyTableSort(long sortType, unsigned long *time)
{
    struct timespec start, end;

    SortFunc sort = getSort(sortType);
    if (sort == NULL)
        return ERR_ARGS;

    if (keyTable.length)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        sort(keyTable.keys, keyTable.length, sizeof(Key), keyTableKey);
        clock_gettime(CLOCK_REALTIME, &end);

        *time = NANO_SEC(end) - NANO_SEC(start);
    }
    else
        return ERR_TABLE;

    return OK;
}


