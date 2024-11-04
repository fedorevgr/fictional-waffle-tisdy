
#ifndef LAB5_SRC_C_MEASURE_H
#define LAB5_SRC_C_MEASURE_H

#include "Service.h"

size_t
measure(
    size_t (*f)(size_t, size_t, bool, bool, ResultData *),
    size_t *averageResultModel,
    size_t *averageResultIdle,
    size_t *errorModel,
    size_t *errorIdle
);

void
printMeasureResults(size_t, size_t, size_t, size_t, size_t);
void
printEstimation(size_t ticks, size_t modelTime);

#endif //LAB5_SRC_C_MEASURE_H
