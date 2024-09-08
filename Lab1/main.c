#include "src/mathing.h"
#include "src/Types.h"
#include "src/IO/IO.h"

ExitCode
enterNumbers_(Number *, Number *);

int
main(void)
{
    ExitCode exitCode;

    Number number1 = {0}, number2 = {0}, result = { 0 };

    exitCode = enterNumbers_(&number1, &number2);

    if (exitCode == OK)
    {
        print(number1);
        printSepLine();
        print(number2);
        printSepLine();
        exitCode = multiply(number1, number2, &result);
        if (exitCode == OK)
            print(result);
    }


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
