#include "BinTree.h"
#include "BinTreeRotators.h"

static BinTree *
treeAddAvl(BinTree *node, Elem key)
{
    if (node == NULL)
        return (newNode(key, 1));

    if (key < node->key)
        node->left = treeAddAvl(node->left, key);
    else if (key > node->key)
        node->right = treeAddAvl(node->right, key);
    else
        return node;

    int balance = treeGetBalance(node);

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

static BinTreeEc
treeAdd_(BinTree **tree, Elem element)
{
    BinTree *newElem = newNode(element, 0);

    if (newElem == nullptr)
        return B_MEMORY;

    if (*tree == nullptr)
    {
        *tree = newElem;
        return B_OK;
    }

    BinTreeEc ec = B_OK;
    BinTree *currNode = *tree, *prevNode;

    while (ec == B_OK && currNode)
    {
        prevNode = currNode;
        if (currNode->key == element)
        {
            free(newElem);
            ec = B_EXISTS;
        }
        else if (currNode->key > element)
            currNode = currNode->left;
        else if (currNode->key < element)
            currNode = currNode->right;
    }

    if (ec == B_OK)
    {
        if (prevNode->key > element)
            prevNode->left = newElem;
        else
            prevNode->right = newElem;
        newElem->parent = prevNode;
    }

    return ec;
}

BinTreeEc
treeAdd(BinTree **tree, Elem element, bool balancing)
{
    if (treeFind(*tree, element))
        return B_EXISTS;

    if (balancing)
        *tree = treeAddAvl(*tree, element);
    else
        treeAdd_(tree, element);

    return B_OK;
}
