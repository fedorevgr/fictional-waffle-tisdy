#include "BinTree.h"
#include "BinTreeRotators.h"
#include "IterCounters.h"

BinTree *nodeBalance(BinTree *node, int key);

static BinTree *
treeAddAvl(BinTree *node, Elem key)
{
    if (node == NULL)
        return newNode(key);

    BinTree *insertingNode;
    counterInc();
    if (key < node->key)
    {
        insertingNode = treeAddAvl(node->left, key);
        node->left = insertingNode;
    }
    else if (key > node->key)
    {
        insertingNode = treeAddAvl(node->right, key);
        node->right = insertingNode;
    }
    else
        return node;
    insertingNode->parent = node;

    int balance = treeGetBalance(node);

    counterInc();
    if (balance > 1)
    {
        counterInc();
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
        counterInc();
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
    BinTree *newElem = newNode(element);

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
        counterInc();
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
