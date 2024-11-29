#ifndef LAB7_HASHMAP_HASHMAPPRIVATE_H
#define LAB7_HASHMAP_HASHMAPPRIVATE_H

#include "Common.h"
#include <stdlib.h>


typedef struct HashMapPrivate_ HashMapPrivate;

typedef enum BlockStatus_
{
    OCCUPIED,
    FREE,
    WAS_OCCUPIED
} BlockStatus;

typedef struct Block_
{
    BlockStatus status;
    TypeVal data;
} Block;

struct HashMapPrivate_ {
    size_t size;
    int elements;
    Block blocks[];
};

HashMapPrivate *hashPriMapInit(size_t size);
void hashPriMapDestroy(HashMapPrivate *hash);
HashMapPrivate *hashPriMapRehash(HashMapPrivate *hash);
HashMapRC hashPriMapAdd(HashMapPrivate **, TypeVal val);
HashMapRC hashPriMapRemove(HashMapPrivate *, TypeKey key);

HashMapRC hashPriMapIn(HashMapPrivate *hash, TypeVal val);
void hashPriPrint(HashMapPrivate *hash);

#endif //LAB7_HASHMAP_HASHMAPPRIVATE_H
