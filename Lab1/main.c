#include "src/mathing.h"
#include "src/Types.h"
#include "src/IO/IO.h"

ExitCode
enterNumbers_(Number *, Number *);

int
main(void)
{
    ExitCode exitCode;

    Number number1 = {0}, number2 = {0};

    exitCode = input(&number1);

    print(number1);

    return exitCode;
}

ExitCode
enterNumbers_(Number *num1, Number *num2)
{
    ExitCode ec = input(num1);

    if (ec == OK)
        ec = input(num2);

    return ec;
}
