#include "Input.h"
#include <stdio.h>

int
main(void)
{
    double number;

    ErrorCode ec = inputDouble(&number);

    printf("%lf\n", number);

    return ec;
}
