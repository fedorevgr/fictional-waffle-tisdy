#include "HashMapPublic.h"
#include <stdlib.h>
#include <assert.h>
#include "IterCounters.h"

#define PRIME_START 2

static bool isPrime_(unsigned number)
{
    bool is = true;
    for (unsigned i = PRIME_START; i <= number / 2 && is; ++i)
        is = (number % i) != 0;
    return is;
}

static unsigned nextPrime_(unsigned previous_number)
{
    previous_number++;
    while (!isPrime_(previous_number))
        previous_number++;

    return previous_number;
}

#define START_SIZE 3
#define OP_TRIGGER 4

int ITER_TRIGGER = OP_TRIGGER;

static TypeKey getHash(TypeVal val, size_t size)
{
    return (TypeKey) (val % size);
}


HashMapPub *hashPubMapInit(size_t size)
{
    if (size == INIT_SIZE)
        size = START_SIZE;

    HashMapPub *hashMap = malloc(sizeof(Node *) * size + sizeof(HashMapPub));
    if (hashMap)
    {
        hashMap->size = size;
        hashMap->elements = 0;
        for (int I = 0; I < hashMap->size; ++I)
            hashMap->blocks[I] = nullptr;
    }

    return hashMap;
}

void hashPubMapDestroy(HashMapPub *hash)
{
    Node *node, *next;
    for (int I = 0; I < hash->size; ++I)
    {
        node = hash->blocks[I];
        while (node)
        {
            next = node->next;
            free(node);
            node = next;
        }
    }
    free(hash);
}

HashMapPub *hashPubMapRehash(HashMapPub *hash)
{
    assert(hash);
    HashMapPub *newHash = hashPubMapInit(nextPrime_(hash->elements));

    if (newHash)
    {
        Node *node;
        for (int I = 0; I < hash->size; ++I)
        {
            node = hash->blocks[I];
            while (node)
            {
                hashPubMapAdd(&newHash, node->data);
                node = node->next;
            }
        }

        hashPubMapDestroy(hash);
    }

    return newHash;
}

HashMapRC hashPubMapAdd(HashMapPub **hashPtr, TypeVal val)
{
    assert(hashPtr);
    HashMapPub *hash = *hashPtr;
    assert(hash);
    if (hash == nullptr)
        return HM_ERROR;

    TypeKey key = getHash(val, hash->size);

    Node *block = hash->blocks[key], *prev = nullptr;
    int triggers = 0;

    while (block)
    {
        if (block->data == val)
            return HM_EXISTS;

        prev = block;
        block = block->next;
        triggers += 1;
        counterInc();
    }

    Node *newNode = malloc(sizeof(Node));

    if (newNode)
    {
        newNode->data = val;
        newNode->next = nullptr;
    }

    if (prev)
        prev->next = newNode;
    else
        hash->blocks[key] = newNode;
    hash->elements += 1;

    if (triggers > ITER_TRIGGER)
        hash = hashPubMapRehash(hash);

    *hashPtr = hash;
    return HM_OK;
}

HashMapRC hashPubMapRemove(HashMapPub *hash, TypeVal val)
{
    TypeKey key = getHash(val, hash->size);

    Node *node = hash->blocks[key], *prevNode = nullptr;
    while (node && node->data != val)
    {
        prevNode = node;
        node = node->next;
        counterInc();
    }

    if (node == NULL)
        return HM_EMPTY;

    hash->elements -= 1;

    if (prevNode)
        prevNode->next = node->next;
    else
        hash->blocks[key] = node->next;

    free(node);
    return HM_OK;
}

HashMapRC hashPubMapIn(HashMapPub *hash, TypeVal val)
{
    TypeKey key = getHash(val, hash->size);

    Node *node = hash->blocks[key];
    counterInc();
    while (node && node->data != val)
    {
        node = node->next;
        counterInc();
    }

    if (node == NULL)
        return HM_EMPTY;
    return HM_OK;
}

#include <stdio.h>
void hashPubPrint(HashMapPub *hash)
{
    printf("Hash Map - Public\n");
    for (size_t i = 0; i < hash->size; ++i)
    {
        printf("%5lu: ", i);

        Node *node = hash->blocks[i];

        if (node)
        {
            printf("%4d", node->data);
            node = node->next;
        }
        else
            printf("x");

        while (node)
        {
            printf(" -> %4d", node->data);
            node = node->next;
        }
        printf("\n");
    }
}

size_t hashPubSize(HashMapPub *hash)
{
    return sizeof(HashMapPub) + sizeof(Node) * hash->elements + sizeof(Node *) * hash->size;
}