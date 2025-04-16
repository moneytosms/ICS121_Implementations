// Author Srimoneyshankar Ajith
//  Title: Kruskals Algorithm
//  Date: 2025-03-24
//  Time: 15:57:38
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int source, destination, weight;
} Edge;

typedef struct
{
    int V, E;
    Edge *edge;
} Graph;

Graph *createGraph(int V, int E)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge *)malloc(graph->E * sizeof(Edge));
    return graph;
}

int find(int subsets[], int i)
{
    if (subsets[i] != i)
    {
        subsets[i] = find(subsets, subsets[i]);
    }
    return subsets[i];
}

void unions(int subsets[], int x, int y)
{
    int a = find(subsets, x);
    int b = find(subsets, y);
    subsets[a] = b;
}

int comparison(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight - b1->weight;
}

void kruskalerbro(Graph *graph)
{
    int V = graph->V;
    Edge result[V]; // Store the resultant MST
    int e = 0; 
    int i = 0;
    int mst_cost = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), comparison);

    int *subsets = (int *)malloc(V * sizeof(int));
    for (int v = 0; v < V; v++)
    {
        subsets[v] = v;
    }

    while (e < V - 1 && i < graph->E)
    {
        Edge next_edge = graph->edge[i++];
        int x = find(subsets, next_edge.source);
        int y = find(subsets, next_edge.destination);

        if (x != y)
        {
            result[e++] = next_edge;
            mst_cost += next_edge.weight;
            unions(subsets, x, y);
        }
    }

    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; i++)
    {
        printf("%d -- %d == %d\n", result[i].source, result[i].destination, result[i].weight);
    } 
    printf("Cost of the MST is %d\n", mst_cost);
}

int main()
{
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    Graph *graph = createGraph(V, E);
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &graph->edge[i].source, &graph->edge[i].destination, &graph->edge[i].weight);
    }

    kruskalerbro(graph);
    return 0;
}
