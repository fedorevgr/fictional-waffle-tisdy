#include "BinTree.h"


// todo: may not work
#define NON_NULL_SUM(res, factor) (result) ? (res + factor) : nullptr

size_t
treeTraverseIn_(BinTree *node, ElemPointerArray result, NodeApplicator applicator)
{
    if (node == nullptr)
        return 0;

    size_t amount = 0;

    if (node->left)
        amount += treeTraverseIn_(node->left, result, applicator);

    if (result)
        result[amount] = &node->key;
    amount += 1;
    if (applicator)
        applicator(node);

    if (node->right)
        amount += treeTraverseIn_(node->right, NON_NULL_SUM(result, amount), applicator);

    return amount;
}

size_t
treeTraversePre_(BinTree *node, ElemPointerArray result, NodeApplicator applicator)
{
    if (node == nullptr)
        return 0;

    size_t amount = 0;

    if (result)
        result[amount] = &node->key;
    amount += 1;
    if (applicator)
        applicator(node);

    if (node->left)
        amount += treeTraversePre_(node->left, NON_NULL_SUM(result, amount), applicator);

    if (node->right)
        amount += treeTraversePre_(node->right, NON_NULL_SUM(result, amount), applicator);


    return amount;
}

size_t
treeTraversePost_(BinTree *node, ElemPointerArray result, NodeApplicator applicator)
{
    if (node == nullptr)
        return 0;

    size_t amount = 0;

    if (node->left)
        amount += treeTraversePost_(node->left, NON_NULL_SUM(result, amount), applicator);

    if (node->right)
        amount += treeTraversePost_(node->right, NON_NULL_SUM(result, amount), applicator);

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
    ElemPointerArray traverseElemPointers = nullptr;

    if (result)
        traverseElemPointers = calloc(MAX_ARRAY_SIZE, sizeof(Elem *));

    size_t amount = 0;


    switch (order)
    {
        case ORDER_IN:amount = treeTraverseIn_(tree, traverseElemPointers, applicator);
            break;
        case ORDER_PREV:amount = treeTraversePre_(tree, traverseElemPointers, applicator);
            break;
        case ORDER_POST:amount = treeTraversePost_(tree, traverseElemPointers, applicator);
            break;
        default:
        {
            free(traverseElemPointers);
            if (result)
                *result = nullptr;
            return 0;
        }
    }

    if (result)
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
