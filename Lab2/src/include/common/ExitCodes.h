//
// Created by Fedor Evgr on 20/09/2024.
//

#ifndef LAB2_EXITCODES_H
#define LAB2_EXITCODES_H

#define MAX_STRING_LENGTH 20

#include <assert.h>

#include "stdlib.h"

typedef enum {
	OK,
	ERR_INPUT,
	ERR_ARGS,
	ERR_TABLE,
    ERR_FILE
} ExitCode;

#endif //LAB2_EXITCODES_H
