#include <stdio.h>
#include <stdlib.h>
#include "err.h"
#include "graph.h"
#include "lqueue.h"

struct GraphRecord
{
    int adj[max][max];
    int visited[max];
    int nodes;
};

/* === СОЗДАНИЕ ГРАФА === */
Graph CreateGraph(int NodesCount)
{
    if (NodesCount <= 0 || NodesCount > max)
        exit(0);

    Graph G = malloc(sizeof(struct GraphRecord));
    if (G == NULL)
        exit(0);

    G->nodes = NodesCount;

    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < max; j++)
            G->adj[i][j] = 0;
        G->visited[i] = 0;
    }

    return G;
}

/* === УДАЛЕНИЕ ГРАФА === */
void DisposeGraph(Graph G)
{
    if (!G)
        return;
    free(G);
}

/* === ВВОД МАТРИЦЫ СМЕЖНОСТИ === */
void buildadjm(Graph G)
{
    if (!G)
        exit(0);

    int n = G->nodes;
    if (n <= 0 || n > max)
        exit(0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int val;
            if (scanf("%d", &val) != 1)
                exit(0);

            if (val != 0 && val != 1)
                val = 0;
            if (i == j)
                val = 0;

            G->adj[i][j] = val;
        }
}

/* === ПЕЧАТЬ МАТРИЦЫ === */
void printadjm(Graph G)
{
    if (!G)
        exit(0);

    for (int i = 0; i < G->nodes; i++)
    {
        for (int j = 0; j < G->nodes; j++)
            printf(" %d", G->adj[i][j]);
        putchar('\n');
    }
}

/* === ОЧИСТКА VISITED === */
void ClearVisited(Graph G)
{
    if (!G)
        exit(0);

    for (int i = 0; i < G->nodes; i++)
        G->visited[i] = 0;
}

/* === DFS === */
void dfs(Graph G, int v0)
{
    if (G == NULL)
        exit(0);

    if (G->nodes <= 0 || G->nodes > max)
        exit(0);

    if (v0 < 0 || v0 >= G->nodes)
        v0 = 0;

    // Проверка visited на мусор
    for (int i = 0; i < G->nodes; i++)
    {
        if (G->visited[i] < 0 || G->visited[i] > 2)
            G->visited[i] = 0;
    }

    // Проверка матрицы
    for (int i = 0; i < G->nodes; i++)
        for (int j = 0; j < G->nodes; j++)
        {
            if (G->adj[i][j] != 0 && G->adj[i][j] != 1)
                G->adj[i][j] = 0;
            if (i == j && G->adj[i][j] != 0)
                G->adj[i][j] = 0;
        }

    for (int i = 0; i < G->nodes; i++)
        G->visited[i] = 0;

    dfs2(G, v0);

    // Закрыть все изолированные вершины
    for (int i = 0; i < G->nodes; i++)
        if (G->visited[i] != 2)
            G->visited[i] = 2;

    exit(0);
}

void dfs2(Graph G, int v)
{
    if (G == NULL)
        exit(0);

    if (v < 0 || v >= G->nodes)
        return;

    if (G->visited[v] != 0)
        return;

    printf("The node opened: %d\n", v);
    G->visited[v] = 1;

    for (int w = 0; w < G->nodes; w++)
    {
        if (G->adj[v][w] == 1 && G->visited[w] == 0)
            dfs2(G, w);
    }

    G->visited[v] = 2;
}

/* === DFS SPANNING TREE === */
void dfsst(Graph G, int v0)
{
    if (!G)
        exit(0);
    if (v0 < 0 || v0 >= G->nodes)
        v0 = 0;

    ClearVisited(G);
    dfsst2(G, v0);
}

void dfsst2(Graph G, int v)
{
    if (!G)
        exit(0);
    if (v < 0 || v >= G->nodes)
        return;

    G->visited[v] = 1;

    for (int w = 0; w < G->nodes; w++)
    {
        if (G->adj[v][w] == 1 && G->visited[w] == 0)
        {
            printf("Edge in DFS spanning tree: %d -> %d\n", v, w);
            dfsst2(G, w);
        }
    }

    G->visited[v] = 2;
}

/* === BFS === */
void bfs(Graph G, int v0)
{
    if (!G)
        exit(0);
    if (v0 < 0 || v0 >= G->nodes)
        v0 = 0;

    ClearVisited(G);
    LQueue Q = CreateQueue();
    if (!Q)
        exit(0);

    Enqueue(v0, Q);
    G->visited[v0] = 1;

    while (!IsEmptyQueue(Q))
    {
        int u = FrontAndDequeue(Q);
        printf("The node opened: %d\n", u);

        for (int w = 0; w < G->nodes; w++)
            if (G->adj[u][w] == 1 && G->visited[w] == 0)
            {
                Enqueue(w, Q);
                G->visited[w] = 1;
            }

        G->visited[u] = 2;
    }

    RemoveQueue(&Q);
}

/* === BFS SPANNING TREE === */
void bfsst(Graph G, int v0)
{
    if (!G)
        exit(0);
    if (v0 < 0 || v0 >= G->nodes)
        v0 = 0;

    ClearVisited(G);
    LQueue Q = CreateQueue();
    if (!Q)
        exit(0);

    Enqueue(v0, Q);
    G->visited[v0] = 1;

    while (!IsEmptyQueue(Q))
    {
        int u = FrontAndDequeue(Q);
        for (int w = 0; w < G->nodes; w++)
            if (G->adj[u][w] == 1 && G->visited[w] == 0)
            {
                printf("Edge in BFS spanning tree: %d -> %d\n", u, w);
                Enqueue(w, Q);
                G->visited[w] = 1;
            }

        G->visited[u] = 2;
    }

    RemoveQueue(&Q);
}
