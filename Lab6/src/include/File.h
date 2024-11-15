#ifndef BINARYTREES_SRC_C_FILE_H
#define BINARYTREES_SRC_C_FILE_H

#include "BinTree.h"

typedef enum FileCode_
{
    F_OK,
    F_ERR
} FileCode;

size_t
readFile(const char *filename, Elem **elements);

FileCode
writeFile(const char *filename, const Elem *elements, size_t length);

#endif //BINARYTREES_SRC_C_FILE_H
