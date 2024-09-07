#ifndef LAB1_SRC_UTILS_STRINGUTILS_H
#define LAB1_SRC_UTILS_STRINGUTILS_H

#include <string.h>
#include "../Types.h"

ExitCode
shiftLeft(String string, int shift);

ExitCode
delete(String string, int position);

ExitCode
stripLeft(String string, char);

#endif //LAB1_SRC_UTILS_STRINGUTILS_H
