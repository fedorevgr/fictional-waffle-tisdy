#ifndef LAB8_GRAPH_H
#define LAB8_GRAPH_H
#include <stdio.h>

typedef struct Block_
{
    bool connection;
} Block;

typedef Block *BlockPointer;

typedef struct Graph_
{
    int size;
    int roads;
    const char **townNames;
    BlockPointer matrix[];
} Graph;

Graph *
graphCreate(int size);

Graph *
graphFromFile(const char *filename);

void
townPrint(FILE *file, int I, int J, const char *fromTown, const char *toTown);
void
graphPrint(Graph *graph, const char *filename);

void
graphDestroy(Graph *);

#endif //LAB8_GRAPH_H
