#include "HashMapPrivate.h"
#include "IterCounters.h"

static TypeKey getHash(TypeVal val, size_t size)
{
    return (TypeKey) (val % size);
}

#define SCALE_FACTOR 1.2

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

int INIT_SIZE_ = 5;
int ITER_LIMIT_ = 4;

HashMapPrivate *hashPriMapInit(size_t size)
{
    if (size == INIT_SIZE)
        size = INIT_SIZE_;

    HashMapPrivate *hash = malloc(sizeof(HashMapPrivate) + sizeof(Block) * size);

    if (hash)
    {
        hash->size = size;
        hash->elements = 0;
        for (int I = 0; I < hash->size; ++I)
            hash->blocks[I].status = FREE;
    }

    return hash;
}

void hashPriMapDestroy(HashMapPrivate *hash)
{
    free(hash);
}

HashMapPrivate *hashPriMapRehash(HashMapPrivate *hash)
{
    HashMapPrivate *newHash = hashPriMapInit(nextPrime_((unsigned) ((double) hash->size * SCALE_FACTOR)));
    if (newHash == NULL)
        return newHash;

    newHash->elements = 0;
    for (int I = 0; I < hash->size; ++I)
    {
        if (hash->blocks[I].status == OCCUPIED)
            hashPriMapAdd(&newHash, hash->blocks[I].data);
    }

    hashPriMapDestroy(hash);

    return newHash;
}

HashMapRC hashPriMapAdd(HashMapPrivate **hashPtr, TypeVal val)
{
    HashMapPrivate *hash = *hashPtr;

    if (hash->size == hash->elements)
        hash = hashPriMapRehash(hash);

    TypeKey key = getHash(val, hash->size);

    int I = 0;
    TypeKey attemptIndex;
    for (; I < ITER_LIMIT_; ++I)
    {
        counterInc();
        attemptIndex = (int) ((key + I * I) % hash->size);
        if (hash->blocks[attemptIndex].status == OCCUPIED && hash->blocks[attemptIndex].data == val)
            return HM_EXISTS;

        if (hash->blocks[attemptIndex].status == FREE)
        {
            hash->blocks[attemptIndex].status = OCCUPIED;
            hash->blocks[attemptIndex].data = val;
            break;
        }
    }
    hash->elements += 1;
    if (I == ITER_LIMIT_)
        hash = hashPriMapRehash(hash);

    *hashPtr = hash;
    return HM_OK;
}

HashMapRC hashPriMapRemove(HashMapPrivate *hash, TypeVal val)
{
    TypeKey key = getHash(val, hash->size);

    int I = 0;
    TypeKey attemptIndex;
    for (; I < ITER_LIMIT_; ++I)
    {
        counterInc();
        attemptIndex = (int) ((key + I * I) % hash->size);
        if (hash->blocks[attemptIndex].status == OCCUPIED && hash->blocks[attemptIndex].data == val)
        {
            hash->blocks[attemptIndex].status = WAS_OCCUPIED;
            break;
        }
    }

    if (I == ITER_LIMIT_)
        return HM_EMPTY;
    return HM_OK;
}

HashMapRC hashPriMapIn(HashMapPrivate *hash, TypeVal val)
{
    TypeKey key = getHash(val, hash->size);

    int I = 0;
    TypeKey attemptIndex;
    for (; I < ITER_LIMIT_; ++I)
    {
        counterInc();
        attemptIndex = (int) ((key + I * I) % hash->size);
        if (hash->blocks[attemptIndex].status == OCCUPIED )
        {
            counterInc();
            if (hash->blocks[attemptIndex].data == val)
                return HM_OK;
        }
    }

    return HM_EMPTY;
}

#include <stdio.h>
void hashPriPrint(HashMapPrivate *hash)
{
    printf("Hash map private\n");
    for (int I = 0; I < hash->size; ++I)
    {
        printf("%4d: ", I);

        switch (hash->blocks[I].status)
        {
            case OCCUPIED: printf("%d", hash->blocks[I].data);
                break;
            case FREE:break;
            case WAS_OCCUPIED:printf("x");
                break;
        }
        printf("\n");
    }
}

size_t hashPriSize(HashMapPrivate *hash)
{
    return hash->size * sizeof(Block) + sizeof(HashMapPrivate);
}
