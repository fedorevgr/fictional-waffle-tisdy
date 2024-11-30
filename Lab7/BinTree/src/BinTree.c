#include "BinTree.h"
#include <assert.h>
#include "BinTreeRotators.h"
#include "BinTreeEtc.h"
#include "IterCounters.h"

#define MAX(a, b) (((a) > (b)) ? a : b)

BinTree *
newNode(int key)
{
    BinTree *node = malloc(sizeof(BinTree));

    if (node)
    {
        node->key = key;
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

int treeGetBalance(BinTree *node)
{
    if (node == NULL)
        return 0;
    return treeHeight(node->left) - treeHeight(node->right);
}

BinTree *
treeFind(BinTree *tree, Elem element)
{
    while (tree)
    {
        counterInc();
        if (tree->key == element)
            return tree;
        else if (tree->key > element)
        {
            counterInc();
            tree = tree->left;
        }
        else
            tree = tree->right;
    }
    return nullptr;
}


#include <stdio.h>
static FILE *globFile__;

static void
printNode_(BinTree *node)
{
//    if (node->parent)
//        fprintf(globFile__, "%d->%d [color=\"green\"];\n", node->key, node->parent->key);

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

        char buffer[100] = "";
        sprintf(buffer, "dot -Tpng %s -o %s.png", filename, filename);
        system(buffer);
    }
}

int
treeHeight(BinTree *tree)
{
    if (tree == nullptr)
        return 0;

    counterInc();
    size_t height = 1, heightL = 0, heightR = 0;
    if (tree->left)
    {
        heightL = treeHeight(tree->left);
        heightL = MAX(heightL, height);
    }
    if (tree->right)
    {
        heightR = treeHeight(tree->right);
        heightR = MAX(heightR, height);
    }

    height += MAX(heightL, heightR);

    return height;
}

size_t
treeLayers(BinTree *tree, int *layersArray)
{
    if (tree == nullptr)
        return 0;

    *layersArray += 1;

    size_t height = 1, heightL = 0, heightR = 0;
    if (tree->left)
    {
        heightL = treeLayers(tree->left, layersArray + 1);
        heightL = MAX(heightL, height);
    }
    if (tree->right)
    {
        heightR = treeLayers(tree->right, layersArray + 1);
        heightR = MAX(heightR, height);
    }

    height += MAX(heightL, heightR);

    return height;
}

size_t
treeSave(BinTree *tree, ElemPointerArray sorted)
{
    return treeSort(tree, sorted);
}
