
#ifndef LAB5_SRC_C_SERVICE_H
#define LAB5_SRC_C_SERVICE_H

#include <stdio.h>

#define TIME_FACTOR 1e5
#define TIME_MIN 0
#define TIME_MAX_T1 (0.6 * TIME_FACTOR)
#define TIME_MAX_T2 (0.1 * TIME_FACTOR)

#define POOL_LIMIT 1000

#define BILLION 1000000000
#define MK_SEC 1000
#define M_SEC (MK_SEC * 1000)

#define NANO_SEC(time) (time.tv_sec * BILLION + time.tv_nsec)
#define MICRO_SEC(nanoseconds) (nanoseconds / MK_SEC)
#define MILLI_SEC(ns) (ns / M_SEC)
#define SEC(ns) (ns / BILLION)

typedef struct RData_
{
    size_t timeModel;
    size_t elementsIn;
    size_t elementsOut;
    size_t OATriggers;
    size_t timeIdle;
} ResultData;

size_t
simulateArrayQueue(size_t maxPoolTime, size_t maxServeTime, bool verbose, bool showAddresses, ResultData *results);

size_t
simulateListQueue(size_t maxPoolTime, size_t maxServeTime, bool verbose, bool showAddresses, ResultData *results);

void
serviceExperiment(void);

#endif //LAB5_SRC_C_SERVICE_H
