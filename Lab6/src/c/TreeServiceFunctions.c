#include "BinTree.h"
#include "File.h"
#include "PrimitiveInput.h"

#include <stdio.h>

BinTreeEc serviceRead(BinTree **tree, const char *filename)
{
    Elem *array = nullptr;
    size_t length = readFile(filename, &array);

    if (array == nullptr)
        return B_MEMORY;

    if (length > 0)
    {
        for (size_t i = 0; i < length; ++i)
            treeAdd(tree, array[i]);
    }
    else
        *tree = nullptr;

    if (array)
        free(array);

    return B_OK;
}

BinTreeEc serviceWrite(BinTree *tree, const char *filename)
{
    Elem *elems = nullptr;
    size_t amount = treeSort(tree, &elems);
    FileCode code = writeFile(filename, elems, amount);
    if (code != F_OK)
    {
        printf("Error file\n");
        return B_UNK_ERR;
    }
    if (elems)
        free(elems);

    return B_OK;
}

BinTreeEc servicePrint(BinTree *tree)
{
    char filename[MAX_BUFFER_LENGTH + 2] = "";

    printf("Enter filename: ");
    InputError inputEC = inputString(filename);
    if (inputEC == INPUT_OK)
        treePrint(tree,filename);
    else
        return B_UNK_ERR;
    return B_OK;
}

BinTreeEc serviceAdd(BinTree **tree)
{
    long newElement;
    printf("Input new element value: ");
    if (inputSigned(&newElement) != INPUT_OK)
    {
        printf("Illegal number\n");
        return B_UNK_ERR;
    }

    BinTreeEc ec = treeAdd(tree, (Elem) newElement);
    if (ec == B_EXISTS)
        printf("Element already in tree\n");
    else if (ec == B_MEMORY)
        printf("Error memory\n");

    return ec;
}

BinTreeEc serviceRemove(BinTree **tree)
{
    long newElement;
    printf("Input remove element value: ");
    if (inputSigned(&newElement) != INPUT_OK)
    {
        printf("Illegal number\n");
        return B_UNK_ERR;
    }

    BinTreeEc ec = treeRemove(tree, (Elem) newElement);
    if (ec == B_EMPTY)
        printf("Element already in tree\n");
    else if (ec == B_MEMORY)
        printf("Error memory\n");

    return ec;
}

BinTreeEc serviceAddFile(const char *file)
{
    long newElement;
    printf("Input new element value: ");
    if (inputSigned(&newElement) != INPUT_OK)
    {
        printf("Illegal number\n");
        return B_UNK_ERR;
    }

    Elem *elements = nullptr;
    size_t length = readFile(file, &elements);

    if (!elements)
    {
        printf("Error memory\n");
        return B_MEMORY;
    }

    if (length < MAX_ARRAY_SIZE)
    {
        elements[length] = (Elem) newElement;
        length++;
        writeFile(file, elements, length);
    }
    else
        printf("Can't add\n");

    if (elements)
        free(elements);

    return B_OK;
}

BinTreeEc serviceRemoveFile(const char *file)
{
    long newElement;
    printf("Input new element value: ");
    if (inputSigned(&newElement) != INPUT_OK)
    {
        printf("Illegal number\n");
        return B_UNK_ERR;
    }

    Elem *elements = nullptr;
    size_t length = readFile(file, &elements);

    if (!elements)
    {
        printf("Error memory\n");
        return B_MEMORY;
    }

    if (length)
    {
        size_t shift = 0;
        for (size_t i = 0; i < length; ++i)
        {
            if (elements[i] == newElement)
            {
                shift += 1;
                continue;
            }
            elements[i - shift] = elements[i];
        }
        length -= shift;
        writeFile(file, elements, length);
    }
    else
        printf("Can't remove - empty\n");

    if (elements)
        free(elements);

    return B_OK;
}

BinTreeEc serviceFind(BinTree *tree)
{
    long newElement;
    printf("Input element value: ");
    if (inputSigned(&newElement) != INPUT_OK)
    {
        printf("Illegal number\n");
        return B_UNK_ERR;
    }

    BinTree *foundNode = treeFind(tree, (Elem) newElement);

    if (foundNode)
    {
        printf("Save node\n");
        servicePrint(foundNode);
    }
    else
        printf("No node with value\n");

    return (foundNode) ? B_OK : B_EMPTY;
}

static void applicatorPrint(BinTree *node)
{
    printf("%d ", node->key);
}

BinTreeEc serviceTraverse(BinTree *tree)
{
    long traverseType;
    printf("Input new element value: ");
    if (inputSigned(&traverseType) != INPUT_OK)
    {
        printf("Illegal number\n");
        return B_UNK_ERR;
    }
    treeTraverse(tree, (Order) traverseType, nullptr, applicatorPrint);
    return B_OK;
}

BinTreeEc serviceSort(BinTree *tree)
{
    printf("Sorted array:\n");
    treeTraverse(tree, ORDER_IN, nullptr, applicatorPrint);
    printf("\n");
    return B_OK;
}

BinTreeEc serviceLevel(BinTree *tree)
{
    int *layers = calloc(MAX_ARRAY_SIZE, sizeof(int));
    if (layers)
    {
        size_t length = treeLayers(tree,layers);
        if (length)
        {
            for (size_t i = 0; i < length; ++i)
                printf("%lu - %d nodes\n", i, layers[i]);

        }
        free(layers);
        return B_OK;
    }
    return B_MEMORY;
}