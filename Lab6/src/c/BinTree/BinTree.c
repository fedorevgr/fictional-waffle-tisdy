#include "BinTree.h"
#include <assert.h>

#define MAX(a, b) (((a) > (b)) ? a : b)

BinTree *
newNode(void)
{
    BinTree *node = malloc(sizeof(BinTree));

    if (node)
    {
        node->key = 0;
        node->right = node->left = node->parent = nullptr;
    }

    return node;
}

size_t
treeTraversePost_(BinTree *node, ElemPointerArray result, NodeApplicator applicator);

static void nodeDestroyer_(BinTree *node)
{
    free(node);
}

void
treeDestroy(BinTree *tree)
{
    treeTraversePost_(tree, nullptr, nodeDestroyer_);
}

BinTreeEc
treeAdd(BinTree **tree, Elem element)
{
    BinTree *newElem = newNode();

    if (newElem == nullptr)
        return B_MEMORY;

    newElem->key = element;

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


BinTree *
treeFind(BinTree *tree, Elem element)
{
    while (tree)
    {
        if (tree->key == element)
            return tree;
        else if (tree->key > element)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return nullptr;
}

size_t
treeSort(BinTree *tree, ElemPointerArray sorted)
{
    Elem *sortedArray = nullptr;
    ElemPointerArray elementsPointers = nullptr;
    size_t size = treeTraverse(tree, ORDER_IN, &elementsPointers, nullptr);

    if (size)
    {
        sortedArray = calloc(size, sizeof(Elem));

        if (sortedArray)
        {
            for (size_t i = 0; i < size; ++i)
                sortedArray[i] = *(elementsPointers[i]);
        }
    }

    free(elementsPointers);

    *sorted = sortedArray;
    return size;
}

#include <stdio.h>

//static void printNode(FILE* file, BinTree *node)
//{
//    if (node->left)
//    {
//        printf("%d -> %d\n", node->key, node->left->key);
//        printNode(file, node->left);
//    }
//
//    if (node->right)
//    {
//        printf("%d -> %d\n", node->key, node->right->key);
//        printNode(file, node->right);
//    }
//}

static FILE *globFile__;

static void
printNode_(BinTree *node)
{
    if (node->left)
        fprintf(globFile__, "%d->%d;\n", node->key, node->left->key);

    if (node->right)
        fprintf(globFile__, "%d->%d;\n", node->key, node->right->key);
}

void
treePrint(BinTree *tree, char *filename)
{
    FILE *file = (filename) ? fopen(filename, "w") : stdout;
    globFile__ = file;
    if (file)
    {
        fprintf(file, "digraph G {\n");
        treeTraversePost_(tree, nullptr, printNode_);
        fprintf(file, "}\n");
        fclose(file);
        globFile__ = nullptr;
    }
}

size_t
treeLayers(BinTree *tree, int *layersArray)
{
    if (tree == nullptr)
        return 0;

    size_t height = 1;
    if (tree->left)
    {
        *layersArray += 1;
        height = MAX(treeLayers(tree->left, layersArray + 1), height);
    }
    if (tree->right)
    {
        *layersArray += 1;
        height = MAX(treeLayers(tree->right, layersArray + 1), height);
    }
    return height;
}

size_t
treeSave(BinTree *tree, ElemPointerArray sorted)
{
    return treeSort(tree, sorted);
}
