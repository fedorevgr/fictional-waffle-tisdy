#include "Task.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum QueryStatus_
{
    START = -1,
    END = -2
} QueryStatus;

static
void
listAppend_(Path *path, const int town)
{
    Node *newNode = malloc(sizeof(Node));
    if (!newNode)
        return;

    newNode->next = nullptr;
    newNode->town = town;

    if (path->head)
    {
        Node *node = path->head;
        for(; node->next; node = node->next);
        node->next = newNode;
    }
    else
        path->head = newNode;
}

static
bool
listPathIn_(const Path *path, const int townStart, const int townEnd)
{
    if (path->head == NULL || path->head->next == NULL)
        return false;

    for (Node *node = path->head; node->next; node = node->next)
    {
        if (node->town == townStart && node->next->town == townEnd
            ||
            node->town == townEnd && node->next->town == townStart)
            return true;
    }

    return false;
}

static
int
listPop_(Path *path)
{
    if (path->head == NULL)
        return END;

    Node *prev = nullptr;
    Node *node = path->head;
    for (;  node->next; prev = node, node = node->next);

    int val = node->town;
    free(node);
    if (prev)
        prev->next = nullptr;
    else
        path->head = nullptr;

    return val;
}

static
void
listFree(Path *path)
{
    Node *node = path->head, *next;
    for (; node; node = next)
    {
        next = node->next;
        free(node);
    }
    free(path);
}

static
int
getNextTown_(const Graph *graph, const int current, const int last)
{
    for (int I = last + 1; I < graph->size; ++I)
    {
        if (graph->matrix[current][I].connection)
            return I;
    }
    return END;
}

static
int
listLastTown_(const Path *path)
{
    if (path->head == NULL)
        return END;

    Node *node = path->head;
    for (; node->next; node = node->next);

    return node->town;
}


void
printPath(const Path *path, const Graph *graph)
{
    Node *town = path->head;
    if (town == NULL)
    {
        printf("No path\n");
        return;
    }

    for (; town; town = town->next)
        printf("%s -> ", graph->townNames[town->town]);

    printf("\n");
}

/*
 * Berlin -> Leipzig -> Casablanca -> Moscow
 *              ^ prev      ^ curr      ^ next
 */
static
Path *
findPathBetweenTowns_(const Graph *graph, const int from, const int to)
{
    Path *const path = malloc(sizeof(Path));

    if (!path)
        return nullptr;

    path->head = nullptr;
    path->next = nullptr;

    int current = from, next = START;
    int pathLength = 0;
    listAppend_(path, current);

    while (path->head)
    {
        next = getNextTown_(graph, current, next);

        if (next == to && graph->roads == pathLength + 1 && !listPathIn_(path, current, next))
        { // exit - path found
            ++pathLength;
            listAppend_(path, next);
            break;
        }

        if (listPathIn_(path, current, next))
            continue;

        if (next == END)
        {
            next = listPop_(path);
            current = listLastTown_(path);
            pathLength -= 1;

            continue;
        }

        ++pathLength;
        listAppend_(path, next);
        current = next;
        next = START;

    }

    if (path->head == NULL)
    {
        listFree(path);
        return nullptr;
    }

    return path;
}

Path *
findPaths(const Graph *graph)
{
    Path *newPath = nullptr;

    for (int sourceTown = 0; sourceTown < graph->size - 1; ++sourceTown)
    {
        for (int targetTown = sourceTown + 1; targetTown < graph->size; ++targetTown)
        {
            newPath = findPathBetweenTowns_(graph, sourceTown, targetTown);
            if (newPath)
            {
                printPath(newPath, graph);
                return newPath;
            }
        }
    }
    return newPath;
}

#define ARROW_COLOR "red"

static
void
printStrictRoad_(FILE *file, const int I, const int J, const char *fromTown, const char *toTown, int degree)
{
    (fromTown) ? fprintf(file, "\"%s\"", fromTown) : fprintf(file, "%d", I);
    fprintf(file, "->");
    (toTown) ? fprintf(file, "\"%s\"", toTown) : fprintf(file, "%d", J);

    fprintf(file, "[color=\"%s\" label=%d fontcolor=%s fontsize=25]\n", ARROW_COLOR, degree, ARROW_COLOR);
}


void
graphPrintPath(const Graph *graph, const Path *path, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return;

    fprintf(file, "digraph G {\nlayout=circo;\n");
    const char *fromTown;
    const char *toTown;
    for (int I = 0; I < graph->size; ++I)
    {
        fromTown = graph->townNames[I];
        for (int J = I + 1; J < graph->size; ++J)
        {
            toTown = graph->townNames[J];

            if (graph->matrix[I][J].connection)
                townPrint(file, I, J, fromTown, toTown);

        }
    }
    int i = 0;
    for (Node *node = path->head; node->next; node = node->next, i++)
        printStrictRoad_(file, node->town, node->next->town, graph->townNames[node->town], graph->townNames[node->next->town], i);

    fprintf(file, "}\n");

    fclose(file);

    char buffer[100] = "";
    sprintf(buffer, "dot -Tpng %s -o %s.png", filename, filename);
    system(buffer);
}
