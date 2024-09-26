//
// Created by Fedor Evgr on 24/09/2024.
//

#ifndef LAB2_SRC_C_KEYTABLE_H
#define LAB2_SRC_C_KEYTABLE_H
#include "Table.h"
#include "Car.h"
#include "Sorting.h"
#include "common/Macros.h"

typedef struct {
    unsigned long key;
    size_t value;
} Key;

typedef struct
{
    size_t length;
    Key keys[MAX_TABLE_LENGTH];
}
KeyTable;

void
keyTableCreate(void);

KeyTable *keyTableGet(void);

ExitCode
keyTableSort(long sortType, unsigned long *time);

void
keyTablePrint(void);

#endif //LAB2_SRC_C_KEYTABLE_H
