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

BinTree *
newNode(int key);
void
treeDestroy(BinTree *);

BinTreeEc
treeAdd(BinTree **, Elem, bool balancing);

BinTreeEc
treeRemove(BinTree **, Elem, bool balance);

int treeGetBalance(BinTree *node);

int
treeHeight(BinTree *tree);

BinTree *
treeFind(BinTree *, Elem);

#endif //BINARYTREES_SRC_C_BINTREE_H
