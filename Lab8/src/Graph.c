#include "Graph.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Graph *
graphCreate(int size)
{
    if (size < 1)
        return nullptr;

    bool error = false;

    Graph *graph = malloc(size * sizeof(BlockPointer) + sizeof(Graph));
    const char **townNames = calloc(size, sizeof(const char *));

    if (graph && townNames)
    {
        graph->roads = 0;
        graph->size = size;
        graph->townNames = townNames;

        for (int i = 0; i < size && !error; ++i)
        {
            graph->matrix[i] = calloc(size, sizeof(Block));
            error = graph->matrix[i] == NULL;
        }

        if (error)
        {
            graphDestroy(graph);
            graph = nullptr;
        }
    }

    if (error)
    {
        if (graph)
            free(graph);
        if (townNames)
            free(townNames);
    }

    return graph;
}

Graph *
graphFromFile(const char *filename)
{
    char *towns;
    size_t cap = 0;
    ssize_t charRead;

    int valBuffer;
    FILE *file = fopen(filename, "r");

    Graph *graph = nullptr;

    if (file)
    {
        int size = 0;
        char ctrl = 0;
        fscanf(file, "%d%c", &size, &ctrl);
        graph = graphCreate(size);

        charRead = getline(&towns, &cap, file);
        towns[charRead - 1] = '\0';

        for (int I = 0; I < size; ++I)
        {
            graph->townNames[I] = strtok(I == 0 ? towns : nullptr, " ");
            for (int J = 0; J < size; ++J)
            {
                fscanf(file, "%d", &valBuffer);
                graph->matrix[I][J].connection = (bool) valBuffer;
                graph->roads += (bool) valBuffer;
            }
        }

        fclose(file);
        graph->roads /= 2;
    }

    return graph;
}

void
townPrint(FILE *file, int I, int J, const char *fromTown, const char *toTown)
{
    (fromTown) ? fprintf(file, "\"%s\"", fromTown) : fprintf(file, "%d", I);
    fprintf(file, "->");
    (toTown) ? fprintf(file, "\"%s\"", toTown) : fprintf(file, "%d", J);

    fprintf(file, "[arrowhead=none color=grey]\n");
}

void
graphPrint(Graph *graph, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
        return;

    fprintf(file, "digraph G {\n");
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
    fprintf(file, "}\n");

    fclose(file);

    char buffer[100] = "";
    sprintf(buffer, "dot -Tpng %s -o %s.png", filename, filename);
    system(buffer);
}

void
graphDestroy(Graph *graph)
{
    free((char *) graph->townNames[0]);
    free(graph->townNames);

    for (int I = 0; I < graph->size; ++I)
    {
        if (graph->matrix[I] == NULL)
            break;
        free(graph->matrix[I]);
    }
    free(graph);
}
