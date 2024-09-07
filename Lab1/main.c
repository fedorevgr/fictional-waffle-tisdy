#include "src/graphics.h"
#include "src/mathing.h"
#include "src/types.h"
#include "src/input.h"
#include <limits.h>
#include <string.h>
#include "src/utils/validation.h"

// 11111222223333344444
int main(void)
{
    ExitCode exitCode;

    String test = "+71.7e1";

    exitCode = convert(test, NULL);

    return exitCode;
}
