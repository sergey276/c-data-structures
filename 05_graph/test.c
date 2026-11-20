#include <stdio.h>
#include "graph.h"
#include "err.h"

int main()
{
    int n, start;

    printf("Enter number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > max)
    {
        Error("Invalid number of nodes!");
        return 1;
    }

    Graph G = CreateGraph(n);
    if (!G) return 1;

    printf("\n=== Build adjacency matrix ===\n");
    buildadjm(G);

    printf("\n=== Adjacency matrix ===\n");
    printadjm(G);

    printf("\nEnter start node for DFS/BFS: ");
    if (scanf("%d", &start) != 1 || start < 0 || start >= n)
    {
        printf("Invalid start node, using 0.\n");
        start = 0;
    }

    printf("\n=== DFS ===\n");
    dfs(G, start);

    printf("\n=== DFS Spanning Tree ===\n");
    dfsst(G, start);

    printf("\n=== BFS ===\n");
    bfs(G, start);

    printf("\n=== BFS Spanning Tree ===\n");
    bfsst(G, start);

    DisposeGraph(G);
    return 0;
}
