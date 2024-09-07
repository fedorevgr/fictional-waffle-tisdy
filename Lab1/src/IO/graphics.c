#include "graphics.h"

#define NUMS "0    5    10   15   20   25   30   35   40"
#define LINE "|----|----|----|----|----|----|----|----|"

#include <string.h>

void
renderRuler(void)
{
    printf("%*s" NUMS "\n", (int) strlen(PROMPT) - 1, " ");
    printf("%*s" LINE "\n", (int) strlen(PROMPT) - 1, " ");
}


