#ifndef LAB7_BINTREE_BINTREEIO_H
#define LAB7_BINTREE_BINTREEIO_H

#include "BinTree.h"
#include "BinTreeEtc.h"

size_t
treeSave(BinTree *tree, ElemPointerArray sorted);

void
treePrint(BinTree *, char *filename);

#endif //LAB7_BINTREE_BINTREEIO_H
