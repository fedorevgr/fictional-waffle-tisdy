#ifndef LAB8_SRC_TASK_H
#define LAB8_SRC_TASK_H

#include "Graph.h"

typedef struct Node_ Node;

struct Node_
{
    int town;
    Node *next;
};

typedef struct Path_ Path;

struct Path_
{
    Node *head;
    Path *next;
};

Path *findPaths(const Graph *graph);
void graphPrintPath(const Graph *graph, const Path *path, const char *filename);

#endif //LAB8_SRC_TASK_H
