#ifndef LAB2_OUTPUT_H
#define LAB2_OUTPUT_H
#include <stdio.h>
#include <string.h>
#include "../common/ExitCodes.h"

#define WIDTH_NAME   (MAX_STRING_LENGTH)
#define WIDTH_SRC    3
#define WIDTH_CNTRY  2
#define WIDTH_PRICE  10
#define WIDTH_CLR    6

#define WIDTH_GRT    9

#define WIDTH_Y_PRD  (WIDTH_GRT)
#define WIDTH_RUN    8
#define WIDTH_OWNERS 5
#define WIDTH_RPS    5

#define TABLE_HEADER \
"| #  | Name                 |Cntr-Ser| Price      | Color  | Grt/Yprod |-/Mileage | -/Own | -/Fix |\n" \
"|----|----------------------|--------|------------|--------|-----------|----------|-------|-------|\n"

#define INFO "" \
"Входные данные"\
                \

// TODO: info

#define FIND_INFO \
"Searching field - Mileage \n" \
"Searching description - less or equal\n"

#define SORT_INFO \
"Sorting key - price\n"               \
"1. Sort type - selection sort\n" \
"2. Sort type - comb sort\n"

#define REALISATION_INFO \
"1. Table\n" \
"2. Key table (doesn't change the table)\n"


#define MENU \
"1 - print table\n" \
"2 - add car to table\n" \
"3 - delete car\n"   \
"4 - sort table\n" \
"5 - find old car, with 1 owner, with no repairs by manufacturer and price\n"             \
"6 - find in table by Mileage\n"    \
"r - read file\n" \
"s - save to file\n"              \
"i - info\n" \
"q - exit\n" \
"S - run sorting statistics\n"    \
"k - sort and show key table\n"   \



#define SPACES \
"\n\n\n\n\n\n" \


#define SPLITTER \
"-----------------------------------------\n"               \

#endif //LAB2_OUTPUT_H
