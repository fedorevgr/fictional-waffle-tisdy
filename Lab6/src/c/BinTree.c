#include "BinTree.h"
#include <assert.h>
#define MAX_ARRAY_SIZE 256

#define MAX(a, b) (((a) > (b)) ? a : b)

BinTree *
newNode(void)
{
    BinTree *node = malloc(sizeof(BinTree));

    if (node)
    {
        node->key = 0;
        node->right = node->left = nullptr;
    }

    return node;
}

static size_t
treeTraverseIn(BinTree *node, ElemPointerArray result, NodeApplicator applicator);

static void nodeDestroyer(BinTree *node)
{
    free(node);
}

void
treeDestroy(BinTree *tree)
{
    treeTraverseIn(tree, nullptr, nodeDestroyer);
}

BinTreeEc
treeAdd(BinTree **tree, Elem element)
{

}

BinTreeEc
treeRemove(BinTree **tree, Elem element)
{

}

BinTree *
treeFind(BinTree *tree, Elem element)
{

}

// todo: may not work
#define NON_NULL_SUM(res, factor) (result) ? (res + factor) : nullptr

static size_t
treeTraverseIn(BinTree *node, ElemPointerArray result, NodeApplicator applicator)
{
    size_t amount = 0;

    if (node->left)
        amount += treeTraverseIn(node->left, result, applicator);

    if (result)
        result[amount] = &node->key;
    amount += 1;

    if (node->right)
        amount += treeTraverseIn(node->right, NON_NULL_SUM(result, amount), applicator);

    if (applicator)
        applicator(node);

    return amount;
}

static size_t
treeTraversePre(BinTree *node, ElemPointerArray result, NodeApplicator applicator)
{
    size_t amount = 0;

    if (result)
        result[amount] = &node->key;
    amount += 1;


    if (node->left)
        amount += treeTraversePre(node->left, result, applicator);

    if (node->right)
        amount += treeTraversePre(node->right, NON_NULL_SUM(result, amount), applicator);

    if (applicator)
        applicator(node);

    return amount;
}

static size_t
treeTraversePost(BinTree *node, ElemPointerArray result, NodeApplicator applicator)
{
    size_t amount = 0;

    if (node->left)
        amount += treeTraversePost(node->left, result, applicator);

    if (node->right)
        amount += treeTraversePost(node->right, NON_NULL_SUM(result, amount), applicator);

    if (result)
        result[amount] = &node->key;
    amount += 1;

    if (applicator)
        applicator(node);

    return amount;
}

size_t
treeTraverse(BinTree *tree, Order order, ElemPointerArray *result, NodeApplicator applicator)
{
    ElemPointerArray traverseElemPointers = calloc(MAX_ARRAY_SIZE, sizeof(Elem *));

    size_t amount = 0;

    if (traverseElemPointers)
    {
        switch (order)
        {
            case ORDER_IN:amount = treeTraverseIn(tree, traverseElemPointers, applicator);
                break;
            case ORDER_PREV:amount = treeTraversePre(tree, traverseElemPointers, applicator);
                break;
            case ORDER_POST:amount = treeTraversePost(tree, traverseElemPointers, applicator);
                break;
            default:assert(0);
        }
    }

    *result = traverseElemPointers;
    return amount;
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
printNode(BinTree *node)
{
    if (node->left)
        fprintf(globFile__, "%d -> %d\n", node->key, node->left->key);

    if (node->right)
        fprintf(globFile__, "%d -> %d\n", node->key, node->right->key);
}

void
treePrint(BinTree *tree, char *filename)
{
    FILE *file = (filename) ? fopen(filename, "w") : stdout;
    globFile__ = file;
    if (file)
    {
        printNode(tree);

        fclose(file);
    }
    globFile__ = nullptr;
}

size_t
treeLayers(BinTree *tree, int *layersArray)
{
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
