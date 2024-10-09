//
// Created by Fedor Evgr on 06/10/2024.
//

#ifndef LAB3_SRC_C_ARRAYS_H
#define LAB3_SRC_C_ARRAYS_H

#include "Codes.h"
#include <stdlib.h>

ErrorCode
arrayInsert(void *array, size_t *length, size_t size, const void *element, size_t index);

ErrorCode
arrayFind(const void *array, size_t length, size_t size, const void *element, size_t *result);

#endif //LAB3_SRC_C_ARRAYS_H
