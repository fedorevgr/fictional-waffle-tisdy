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
"| #  | Name                 |Cntr-Ser| Price      | Color  | Grt/Yprod | -/Run    | -/Own | -/Fix |\n" \
"|----|----------------------|--------|------------|--------|-----------|----------|-------|-------|\n"

#define INFO "" // TODO: info

#endif //LAB2_OUTPUT_H
