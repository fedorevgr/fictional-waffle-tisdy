#include "BinTree.h"
#include "IterCounters.h"

BinTree *
rotateLeft(BinTree *tree)
{
    BinTree *ancestor = tree->parent;
    BinTree *y = tree->right;
    BinTree *T2 = y->left;

    y->left = tree;
    tree->parent = y;

    tree->right = T2;
    if (T2)
        T2->parent = tree;

    y->parent = ancestor;
    return y;
}

BinTree *
rotateRight(BinTree *tree)
{
    BinTree *ancestor = tree->parent;
    BinTree *x = tree->left;
    BinTree *T2 = x->right;

    x->right = tree;
    tree->parent = x;
    tree->left = T2;
    if (T2)
        T2->parent = tree;

    x->parent = ancestor;
    return x;
}

BinTree *nodeBalance(BinTree *node, int key)
{
    int balance = treeGetBalance(node);
    if (balance == 0)
        return node;

    counterInc();
    if (balance > 1)
    {
        if (key < node->left->key)
            return rotateRight(node);
        else if (key > node->left->key)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    else if (balance < -1)
    {
        if (key > node->right->key)
            return rotateLeft(node);
        else
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

BinTree *treeBalance(BinTree *fromNode)
{
    BinTree *previous = nullptr;
    while (fromNode)
    {
        fromNode = nodeBalance(fromNode, fromNode->key);
        previous = fromNode;
        fromNode = fromNode->parent;
    }

    return previous;
}
