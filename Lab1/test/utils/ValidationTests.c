#include "ValidationTests.h"
#include <stdio.h>
#include "../Tests.h"

#define TESTS  10
int
validationTestPos(void)
{
    PrintInfo();
    char *testNumber[TESTS] = {
        "0.1",
        "0000.01",
        "-.001",
        "+1.0",
        "-1.0",
        "1.0e3",
        "-1.0e-3",
        "1.0e+3",
        "12e3",
        "1324"
    };

    int counter = 0;
    ExitCode code;
    for (int i = 0; i < TESTS; i++)
    {
        code = validateReal(testNumber[i]);

        if (code == OK)
            printf("%d - PASSED - %s\n", i, testNumber[i]), counter++;
        else
            printf("%d - FAIL - %s\n", i, testNumber[i]);

    }

    printf("Status: %d / %d\n", counter, TESTS);

    code = counter == TESTS ? OK : ERROR;

    return code;
}
#undef TESTS

#define TESTS  12
int
validationTestNeg(void) {
    PrintInfo();

    char *testNumber[TESTS] = {
        "a.1",
        "1,000.01",
        "1.0.01",
        "+1..0",
        "-1 0.0",
        "1.0e+",
        "-1.0e-",
        "1.0e++3",
        "12e3.4",
        "1324a",
        "Math",
        "1ee2"
    };
    int counter = 0;
    ExitCode code;
    for (int i = 0; i < TESTS; i++)
    {
        code = validateReal(testNumber[i]);

        if (code != OK)
            printf("%d - PASSED - %s\n", i, testNumber[i]), counter++;
        else
            printf("%d - FAIL - %s\n", i, testNumber[i]);

    }

    printf("Status: %d / %d\n", counter, TESTS);

    code = counter == TESTS ? OK : ERROR;

    return code;
}
#undef TESTS

ExitCode
runValidationTests(void)
{
    ExitCode codePos = validationTestPos();
    ExitCode codeNeg = validationTestNeg();

    return codePos + codeNeg;
}
