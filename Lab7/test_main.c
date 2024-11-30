#include "BinTree/BinTree.h"
#include "BinTree/BinTreeIO.h"
#include <stdio.h>

#include "HashMap/HashMapPublic.h"
#include "HashMap/HashMapPrivate.h"

#define MODE true

#define ARRAY 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 17, 20

void checkPubHash(void);
void checkPriHash(void);

int
main(void)
{
    checkPriHash();
}

void checkPriHash(void)
{
    int keyArr[] = {ARRAY};
    int length = sizeof(keyArr) / 4;

    HashMapPrivate *hash = hashPriMapInit(INIT_SIZE);

    for (int i = 0; i < length; ++i)
    {
        hashPriMapAdd(&hash, keyArr[i]);
        hashPriPrint(hash);
    }
    for (int i = 0; i < length; ++i)
    {
        hashPriMapRemove(hash, keyArr[i]);
        hashPriPrint(hash);
    }

    hashPriMapDestroy(hash);
}

void checkPubHash(void)
{
    int keyArr[] = {ARRAY};
    int length = sizeof(keyArr) / 4;

    HashMapPub *hash = hashPubMapInit(INIT_SIZE);

    for (int i = 0; i < length; ++i)
    {
        hashPubMapAdd(&hash, keyArr[i]);
        hashPubPrint(hash);
    }
    for (int i = 0; i < length; ++i)
    {
        hashPubMapRemove(hash, keyArr[i]);
        hashPubPrint(hash);
    }

    hashPubMapDestroy(hash);
}


void checkBinTree(void)
{
    char buffer[40] = "";
    BinTree *tree = nullptr;
    int keyArr[] = {ARRAY};
    int length = sizeof(keyArr) / 4;

    for (int i = 0; i < length; ++i)
    {
        snprintf(buffer, 30, "cache/Tree_Add_%d.txt", i);
        treeAdd(&tree, keyArr[i], MODE);
        treePrint(tree, buffer);
    }
    for (int i = 0; i < length; ++i)
    {
        snprintf(buffer, 30, "cache/Tree_Remove_%d.txt", i);
        treeRemove(&tree, keyArr[i], MODE);
        treePrint(tree, buffer);
    }
    treeDestroy(tree);
}
