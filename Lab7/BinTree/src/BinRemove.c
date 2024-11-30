#include "BinTree.h"
#include "BinTreeRotators.h"
#include "BinTreeIO.h"
#include <assert.h>
#include "IterCounters.h"

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

    BinTree *startFrom = maximal->parent;

    if (maximal->left)
        removeOneLeaf(tree, *toRemove);
    else
        removeNoLeaf(tree, *toRemove);
    return startFrom;
}

static BinTree *
balanceFromNode(BinTree *fromNode);

BinTreeEc
treeRemove(BinTree **tree, Elem element, bool balance)
{
    BinTree *toRemove = treeFind(*tree, element);

    if (!toRemove)
        return B_EMPTY;

    BinTree *fromNode = toRemove->parent;
    counterInc();
    if (toRemove->left == nullptr && toRemove->right == nullptr)
        removeNoLeaf(tree, toRemove);
    else if (toRemove->left && toRemove->right)
        fromNode = removeTwoLeaves(tree, &toRemove);
    else
        removeOneLeaf(tree, toRemove);

    free(toRemove);

    if (balance && fromNode)
        *tree = balanceFromNode(fromNode);

    return B_OK;
}

static BinTree *
nodeBalance(BinTree *node)
{
    if (node == NULL)
        return node;

    BinTree *parent = nullptr;
    int balance = treeGetBalance(node);

    counterInc();
    if (balance > 1 && treeGetBalance(node->left) >= 0)
        return rotateRight(node);

    counterInc();
    if (balance > 1 && treeGetBalance(node->left) < 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    counterInc();
    if (balance < -1 && treeGetBalance(node->right) <= 0)
        return rotateLeft(node);

    counterInc();
    if (balance < -1 && treeGetBalance(node->right) > 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

static BinTree *
balanceFromNode(BinTree *fromNode)
{
    BinTree *previous = nullptr;
    BinTree *parent;
    while (fromNode)
    {
        fromNode = nodeBalance(fromNode);

        if (fromNode->parent)
        {
            counterInc();
            if (fromNode->parent->key > fromNode->key)
                fromNode->parent->left = fromNode;
            else
                fromNode->parent->right = fromNode;
        }

        previous = fromNode;
        fromNode = fromNode->parent;
    }

    return previous;
}
