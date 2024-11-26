#ifndef LAB7_BINTREE_BINTREEETC_H
#define LAB7_BINTREE_BINTREEETC_H

#include "BinTree.h"

size_t
treeLayers(BinTree *tree, int *layers);
size_t
treeTraverse(BinTree *tree, Order order, ElemPointerArray *result, NodeApplicator applicator);
size_t
treeSort(BinTree *tree, ElemPointerArray sorted);


#endif //LAB7_BINTREE_BINTREEETC_H
