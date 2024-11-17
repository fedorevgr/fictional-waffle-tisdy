#include "BinTree.h"
#include <assert.h>

static void
removeNoLeaf(BinTree **tree, BinTree *toRemove)
{
    BinTree *parent = toRemove->parent;

    if (parent == nullptr)
        *tree = nullptr;
    else
    {
        if (parent->right == toRemove)
            parent->right = nullptr;
        else
            parent->left = nullptr;
    }
}

static void
removeOneLeaf(BinTree **tree, BinTree *toRemove)
{
    BinTree *parent = toRemove->parent;

    BinTree *nextNode = (toRemove->right) ? toRemove->right : toRemove->left;

    if (parent == nullptr)
        *tree = nextNode;
    else
    {
        if (parent->right == toRemove)
            parent->right = nextNode;
        else
            parent->left = nextNode;
    }
    nextNode->parent = parent;
}

#define SWAP(a, b) do { \
                    a ^= b; \
                    b ^= a; \
                    a ^= b; \
                while(0);


static void
removeTwoLeaves(BinTree **tree, BinTree **toRemove)
{
    BinTree *toSwap = *toRemove;
    BinTree *maximal = toSwap->left;

    while (maximal->right)
        maximal = maximal->right;

    toSwap->key = maximal->key;
    *toRemove = maximal;

    if (maximal->left)
    {
        removeOneLeaf(tree, *toRemove);
    }
    else
    {
        removeNoLeaf(tree, *toRemove);
    }
}

BinTreeEc
treeRemove(BinTree **tree, Elem element)
{
    BinTree *toRemove = treeFind(*tree, element);

    if (!toRemove)
        return B_EMPTY;

    if (toRemove->left == nullptr && toRemove->right == nullptr)
    {
        removeNoLeaf(tree, toRemove);
    }
    else if (toRemove->left && toRemove->right)
    {
        removeTwoLeaves(tree, &toRemove);
    }
    else
    {
        removeOneLeaf(tree, toRemove);
    }


    free(toRemove);
    return B_OK;
}
