#include "TreeService.h"
#include "BinTree/BinTreeEtc.h"
#include "IterCounters.h"
#include "Common.h"

#include "PrimitiveInput.h"
#include "File.h"
#include <stdio.h>

void serviceTree(bool avl)
{
    char filename[MAX_BUFFER_LENGTH + 2] = "";
    if (enterFile(filename) != 0)
        return;

    int *elements = nullptr;
    size_t elemAmount = readFile(filename, &elements);

    BinTree *binTree = nullptr;

    if (elements && elemAmount)
    {
        for (int I = 0; I < elemAmount; ++I)
            treeAdd(&binTree, elements[I], avl);

        free(elements);
    }

    Mode mode;
    BinTreeEc error;
    int elemBuffer;
    size_t size;
    BinTree *found;
    do
    {
        size = treeTraverse(binTree, ORDER_IN, nullptr, nullptr) * sizeof(BinTree);
        printf("Current size: %lu bytes\n", size);
        mode = getMode();

        if (mode == ADD || mode == DELETE || mode == FIND)
        {
            long newElement;
            printf("Input new element value: ");
            if (inputSigned(&newElement) != INPUT_OK)
            {
                printf("Illegal number\n");
                mode = OP_ERROR;
            }
            elemBuffer = (int) newElement;
        }

        counterGet();
        switch (mode)
        {
            case ADD:
                error = treeAdd(&binTree, elemBuffer, avl);
                printf("Compares: %d\n", counterGet());

                if (error == B_EXISTS)
                    printf("Error: Element exists\n");

                break;
            case DELETE:
                error = treeRemove(&binTree, elemBuffer, avl);
                printf("Compares: %d\n", counterGet());

                if (error == B_EMPTY)
                    printf("Error: No such element\n");

                break;
            case FIND:
                found = treeFind(binTree, elemBuffer);
                printf("Compares: %d\n", counterGet());

                if (found == NULL)
                    printf("Error: No such element\n");
                else
                    treePrint(found, "found_tree");

                break;
            case PRINT:
                treePrint(binTree, "current_tree");
                break;
            case QUIT:printf("Quitting...\n");
                break;
            case OP_ERROR:printf("Error, try again...\n");
                break;
        }
    }
    while (mode != QUIT);
    treeDestroy(binTree);
}

