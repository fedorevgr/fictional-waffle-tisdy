#include "MathingTest.h"
#include "Tests.h"

#define TESTS 11
#define number(_s, _value, _length, _exp) { \
              .sign = _s, .value = _value, .valueLength = _length, .exponent = _exp                              \
            }
ExitCode
mathingPos(void)
{
    Number nums1[TESTS] = {
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


}
#undef TESTS

