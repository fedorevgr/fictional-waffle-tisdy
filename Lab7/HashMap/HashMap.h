#ifndef LAB7_HASHMAP_HASHMAP_H
#define LAB7_HASHMAP_HASHMAP_H

#include "List/List.h"
#include <stdlib.h>

typedef enum HashingType_
{
    PUBLIC,
    PRIVATE
} HashingType;

typedef enum HashMapRC_
{
    HM_OK,
    HM_ERROR,
    HM_FULL,
    HM_EMPTY
} HashMapRC;

typedef struct HashMap_ HashMap;

typedef struct HashBlock_ {
    Node *list;
} HashBlock;

struct HashMap_ {
    HashingType type;
    size_t size;
    HashBlock blocks[];
};

typedef int TypeKey;
typedef int TypeVal;

typedef struct BlockData_
{
    TypeKey key;
    TypeVal val;
} BlockData;

HashMap *hashMapInit(HashingType type);
HashMapRC hashMapAdd(TypeKey key, TypeVal value);
HashMapRC hashMapRemove(TypeKey key);
HashMapRC hashMapGet(TypeKey key, TypeVal *val);

#endif //LAB7_HASHMAP_HASHMAP_H
