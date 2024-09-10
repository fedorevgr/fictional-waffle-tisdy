#ifndef LAB1_SRC_UTILS_STRINGUTILS_H
#define LAB1_SRC_UTILS_STRINGUTILS_H

#include <string.h>
#include "../../Types.h"

ExitCode
shiftLeft(String string, int shift);

ExitCode
delete(String string, int position);

int
stripLeft(String string, char);

int
stripRight(const char *, char *stringEnd, char c);

#endif //LAB1_SRC_UTILS_STRINGUTILS_H
