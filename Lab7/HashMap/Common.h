#ifndef LAB7_HASHMAP_COMMON_H
#define LAB7_HASHMAP_COMMON_H

#define INIT_SIZE 0

typedef enum HashMapRC_
{
    HM_OK,
    HM_ERROR,
    HM_FULL,
    HM_EMPTY,
    HM_EXISTS
} HashMapRC;

typedef int TypeKey;
typedef int TypeVal;


#endif //LAB7_HASHMAP_COMMON_H
