#ifndef LAB7_HASHMAP_HASHMAP_H
#define LAB7_HASHMAP_HASHMAP_H

#include "List/List.h"
#include <stdlib.h>

#include "Common.h"

typedef struct HashMapPub_ HashMapPub;

struct HashMapPub_ {
    size_t size;
    int elements;
    Node *blocks[];
};

HashMapPub *hashPubMapInit(size_t size);
void hashPubMapDestroy(HashMapPub *hash);
HashMapPub *hashPubMapRehash(HashMapPub *hash);
HashMapRC hashPubMapAdd(HashMapPub **, TypeVal val);
HashMapRC hashPubMapRemove(HashMapPub *, TypeKey key);

HashMapRC hashPubMapIn(HashMapPub *hash, TypeVal val);
void hashPubPrint(HashMapPub *hash);
size_t hashPubSize(HashMapPub *hash);

#endif //LAB7_HASHMAP_HASHMAP_H
