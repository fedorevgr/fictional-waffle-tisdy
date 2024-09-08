#include "InputTests.h"
#include <string.h>
#include "Tests.h"

#define TEST_STRINGS  \
        "3.14159", \
        "0.0001", \
        "1e5", \
        "-42", \
        "1024", \
        ".003", \
        "0", \
        "-.08", \
        "-.1e1", \
        "6E-2", \
        "1.0e1" \


typedef enum errors
{
    CMP_OK,
    CMP_SIGN,
    CMP_VALUE,
    CMP_EXP
} ErrorsCompare;

ErrorsCompare
compareNumbers_(Number a, Number b)
{
    if (a.sign != b.sign)
        return CMP_SIGN;

    if (a.exponent != b.exponent)
        return CMP_EXP;

    if (a.valueLength != b.valueLength)
        return CMP_VALUE;

    if (strcmp((char *) a.value, (char *) b.value) != 0)
        return CMP_VALUE;

    return CMP_OK;
}

#define TESTS    11
ExitCode
testInputPos(void)
{
    PrintInfo();
    char *untouchables[TESTS] = {TEST_STRINGS};
    char numbers[][TESTS] = {TEST_STRINGS};

    Number realResults[TESTS] = {0};

    Number check[TESTS] = {
        {.sign = 0, .value = {3, 1, 4, 1, 5, 9}, .valueLength = 6, .exponent = 1},
        {.sign = 0, .value = {1}, .valueLength = 1, .exponent = -3},
        {.sign = 0, .value = {1}, .valueLength = 1, .exponent = 6},
        {.sign = 1, .value = {4, 2}, .valueLength = 2, .exponent = 2},
        {.sign = 0, .value = {1, 0, 2, 4}, .valueLength = 4, .exponent = 4},
        {.sign = 0, .value = {3}, .valueLength = 1, .exponent = -2},
        {.sign = 0, .value = {0}, .valueLength = 1, .exponent = 0},
        {.sign = 1, .value = {8}, .valueLength = 1, .exponent = -1},
        {.sign = 1, .value = {1}, .valueLength = 1, .exponent = 1},
        {.sign = 0, .value = {6}, .valueLength = 1, .exponent = -1},
        {.sign = 0, .value = {1, 0}, .valueLength = 2, .exponent = 2},
    };

    int counter = 0;
    for (int i = TO_START; i < TESTS; i++)
    {
        convert_(numbers[i], realResults + i);

        if (compareNumbers_(realResults[i], check[i]) == CMP_OK)
            printf("%d / %d: %s : %s\n", i + 1, TESTS, "PASS", untouchables[i]), counter++;
        else
            printf("%d / %d: %s : %s\n", i + 1, TESTS, "FAIL", untouchables[i]);
    }
    printf("Status: %d / %d\n", counter, TESTS);
    return counter == TESTS ? OK : ERROR;
}
#undef TESTS


ExitCode
runInputTest(void)
{
    ExitCode code = testInputPos();
    return code;
}
