#ifndef BINARYTREES_SRC_C_FILE_H
#define BINARYTREES_SRC_C_FILE_H

#include <stdlib.h>

typedef enum FileCode_
{
    F_OK,
    F_ERR
} FileCode;

size_t
readFile(const char *filename, int **elements);

FileCode
writeFile(const char *filename, const int *elements, size_t length);

FileCode
addToFile(const char *filename, int elem);

FileCode
removeFromFile(const char *filename, int elem);

FileCode
fileFind(const char *filename, const int elem);

size_t
fileSize(const char *filename);

#endif //BINARYTREES_SRC_C_FILE_H
