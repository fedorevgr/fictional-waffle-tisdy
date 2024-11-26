#include "BinTree.h"
#include "BinTreeRotators.h"
#include <assert.h>

static BinTree *
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
    return parent;
}

static BinTree *
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
    return nextNode;
}

static BinTree *
removeTwoLeaves(BinTree **tree, BinTree **toRemove)
{
    BinTree *toSwap = *toRemove;
    BinTree *maximal = toSwap->left;

    while (maximal->right)
        maximal = maximal->right;

    toSwap->key = maximal->key;
    *toRemove = maximal;

    if (maximal->left)
        return removeOneLeaf(tree, *toRemove);
    else
        return removeNoLeaf(tree, *toRemove);
}

BinTreeEc
treeRemove(BinTree **tree, Elem element, bool balance)
{
    BinTree *toRemove = treeFind(*tree, element);

    if (!toRemove)
        return B_EMPTY;

    BinTree *fromNode;
    if (toRemove->left == nullptr && toRemove->right == nullptr)
        fromNode = removeNoLeaf(tree, toRemove);
    else if (toRemove->left && toRemove->right)
        fromNode = removeTwoLeaves(tree, &toRemove);
    else
        fromNode = removeOneLeaf(tree, toRemove);

    free(toRemove);

    if (balance)
        *tree = treeBalance(fromNode);

    return B_OK;
}
