#ifndef LAB2_INPUT_H
#define LAB2_INPUT_H

#include "../common/ExitCodes.h"

#include <stdio.h>
#include <string.h>

ExitCode
inputString(char *buffer, int limit);

ExitCode
inputLong(long *buffer);

ExitCode
inputUnsignedLong(unsigned long *buffer);

#endif //LAB2_INPUT_H
