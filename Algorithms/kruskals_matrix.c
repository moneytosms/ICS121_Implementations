#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

int parent[MAX];

// Function to find the parent of a node
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Function to perform union of two subsets
void unionSets(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

// Function to implement Kruskal's algorithm
void kruskals(int graph[MAX][MAX], int n) {
    Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Extract edges from the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != 0 && graph[i][j] != INT_MAX) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges by weight
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Initialize parent array
    for (int i = 0; i < n; i++)
        parent[i] = i;

    printf("Edges in the Minimum Spanning Tree:\n");
    int mstWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        // Check if including this edge forms a cycle
        if (find(u) != find(v)) {
            printf("Edge (%d, %d) with weight %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
            unionSets(u, v);
        }
    }

    printf("Total weight of the Minimum Spanning Tree: %d\n", mstWeight);
}

int main() {
    int n;
    int graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use %d for infinity):\n", INT_MAX);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    kruskals(graph, n);

    return 0;
}