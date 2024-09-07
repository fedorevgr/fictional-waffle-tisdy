#ifndef LAB1_SRC_INPUT_H
#define LAB1_SRC_INPUT_H

#include "graphics.h"
#include "../mathing.h"
#include "../Types.h"

ExitCode
enter_(char *buffer);

ExitCode
convert_(String rawNumber, Number *number);

#endif //LAB1_SRC_INPUT_H
