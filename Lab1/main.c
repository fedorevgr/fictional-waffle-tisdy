#include "src/mathing.h"
#include "src/Types.h"
#include "src/IO/IO.h"

ExitCode
enterNumbers_(Number *, Number *);

int
main(void)
{
    ExitCode exitCode;

    Number number1 = {0, .posFirst=true}, number2 = {0}, result = { 0 };

    exitCode = enterNumbers_(&number1, &number2);

    if (exitCode == OK)
    {
        print(number1);
        print(number2);

        exitCode = multiply(number1, number2, &result);
    }

    showResult(exitCode, result);

    return exitCode;
}

#include "src/IO/graphics.h"
ExitCode
enterNumbers_(Number *num1, Number *num2)
{
    renderPrompt();
    ExitCode ec = input(num1);

    if (ec == OK)
    {
        renderPrompt();
        ec = input(num2);
    }

    return ec;
}
