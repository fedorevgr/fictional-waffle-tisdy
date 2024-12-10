#include "src/Task.h"
#include "src/Graph.h"

#define TEMP_FILENAME "Small.graph"

int
main(int argc, char **argv)
{
    if (argc != 2)
        return -1;

    Graph *graph = graphFromFile(argv[1]);
    if (!graph)
    {
        printf("Error: No graph\n");
        return -1;
    }

    Path *path = findPaths(graph);

    graphPrint(graph, "CoolGraph");

    if (path)
        graphPrintPath(graph, path, "CoolPath");
    else
        printf("No path found\n");

    graphDestroy(graph);
	return 0;
}

