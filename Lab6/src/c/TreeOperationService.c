#include "TreeOperationService.h"
#include <stdio.h>

BinTreeEc serviceRead(BinTree **tree, const char *filename);
BinTreeEc serviceWrite(BinTree *tree, const char *filename);
BinTreeEc servicePrint(BinTree *tree);

BinTreeEc serviceAdd(BinTree **tree);
BinTreeEc serviceRemove(BinTree **tree);

BinTreeEc serviceAddFile(const char *file);
BinTreeEc serviceRemoveFile(const char *file);

BinTreeEc serviceFind(BinTree *tree);
BinTreeEc serviceTraverse(BinTree *tree);
BinTreeEc serviceSort(BinTree *tree);
BinTreeEc serviceLevel(BinTree *tree);

#define MENU "Tree actions:\n" \
            " - W - save tree\n"           \
            " - P - print\n"                   \
            " - A - add to tree\n" \
            " - a - add to file\n" \
            " - D - delete from tree\n"  \
            " - d - delete from file\n"  \
            " - F - find \n"   \
            " - T - traverse\n"\
            " - S - sort\n"    \
            " - L - show levels\n" \
            " - q - quit\n"


typedef enum Mode_
{
    // READ = 'R',
    WRITE = 'W',
    ADD = 'A',
    ADD_FILE = 'a',
    REMOVE = 'D',
    REMOVE_FILE = 'd',
    FIND = 'F',
    TRAVERSE = 'T',
    SORT = 'S',
    LEVEL = 'L',
    QUIT = 'q',
    PRINT = 'P',
    TREE_MODE_ERR
} TreeMode;

#include "PrimitiveInput.h"
TreeMode getMode(void)
{
    char buff[MAX_BUFFER_LENGTH + 2] = "";

    InputError er = inputString(buff);
    if (er != INPUT_OK)
        return TREE_MODE_ERR;

    return buff[0];
}

void service(void)
{
    TreeMode treeMode;
    BinTree *tree = nullptr;
    BinTreeEc ec;
    char filename[MAX_BUFFER_LENGTH + 2] = "";

    printf("Enter file with numbers: ");
    if (inputString(filename) != INPUT_OK)
    {
        printf("Error: input string\n");
        return;
    }

    {
        FILE *file = fopen(filename, "r");
        if (!file)
        {
            printf("File may not exist, creating...\n");
            file = fopen(filename, "w");

            if (!file)
            {
                printf("Error: file\n");
                return;
            }
            fclose(file);
            printf("File %s created\n", filename);
        }
        fclose(file);
    }

    serviceRead(&tree, filename);

    do
    {
        printf(MENU);
        treeMode = getMode();

        switch (treeMode)
        {
            case WRITE:ec = serviceWrite(tree, filename);
                break;
            case PRINT:ec = servicePrint(tree);
                break;
            case ADD:ec = serviceAdd(&tree);
                break;
            case ADD_FILE:ec = serviceAddFile(filename);
                break;
            case REMOVE:ec = serviceRemove(&tree);
                break;
            case REMOVE_FILE:ec = serviceRemoveFile(filename);
                break;
            case FIND:ec = serviceFind(tree);
                break;
            case TRAVERSE:ec = serviceTraverse(tree);
                break;
            case SORT:ec = serviceSort(tree);
                break;
            case LEVEL:ec = serviceLevel(tree);
                break;
            case QUIT:printf("Quitting...\n");
                ec = B_OK;
                break;
            default:printf("Error: Illegal option\n");
        }

        if (ec != B_OK)
            printf("ERROR\n");
    }
    while (treeMode != QUIT);

    treeDestroy(tree);
}

