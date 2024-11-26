#include "BinTree.h"

BinTree *
rotateLeft(BinTree *tree)
{
    BinTree *y = tree->right;
    BinTree *T2 = y->left;

    y->left = tree;
    tree->right = T2;

    return y;
}

BinTree *
rotateRight(BinTree *tree)
{
    BinTree *x = tree->left;
    BinTree *T2 = x->right;

    x->right = tree;
    tree->left = T2;

    return x;
}

BinTree *nodeBalance(BinTree *node)
{
    int balance = treeGetBalance(node);
    int key = node->key;

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
    BinTree *previous;
    while (fromNode)
    {
        fromNode = nodeBalance(fromNode);
        previous = fromNode;
        fromNode = fromNode->parent;
    }

    return previous;
}
