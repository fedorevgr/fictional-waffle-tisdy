#ifndef BINARYTREES_SRC_C_BINTREE_H
#define BINARYTREES_SRC_C_BINTREE_H
#include <stdlib.h>
#define MAX_ARRAY_SIZE 256

typedef int Elem;
typedef Elem **ElemPointerArray;

typedef struct BinaryTree_ BinTree;

struct BinaryTree_
{
    Elem key;
    BinTree *left;
    BinTree *right;
    BinTree *parent;
};

typedef enum BinTreeEc_
{
    B_OK,
    B_UNK_ERR,
    B_EMPTY,
    B_EXISTS,
    B_MEMORY
} BinTreeEc;

typedef enum Order_
{
    ORDER_PREV,
    ORDER_IN,
    ORDER_POST
} Order;

typedef void (*NodeApplicator)(BinTree *);

void
treeDestroy(BinTree *);

BinTreeEc
treeAdd(BinTree **, Elem);
BinTreeEc
treeRemove(BinTree **, Elem);

BinTree *
treeFind(BinTree *, Elem);
size_t
treeTraverse(BinTree *tree, Order order, ElemPointerArray *result, NodeApplicator applicator);
size_t
treeSort(BinTree *tree, ElemPointerArray sorted);

void
treePrint(BinTree *, char *filename);
size_t
treeLayers(BinTree *tree, int *layers);
size_t
treeSave(BinTree *tree, ElemPointerArray sorted);

#endif //BINARYTREES_SRC_C_BINTREE_H
