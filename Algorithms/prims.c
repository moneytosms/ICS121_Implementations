#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Function to find the vertex with the minimum key value
int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the constructed Minimum Spanning Tree
void printMST(int parent[], int graph[MAX][MAX], int n) {
    printf("Edges in the Minimum Spanning Tree:\n");
    int mstWeight = 0;
    for (int i = 1; i < n; i++) {
        printf("Edge (%d, %d) with weight %d\n", parent[i], i, graph[i][parent[i]]);
        mstWeight += graph[i][parent[i]];
    }
    printf("Total weight of the Minimum Spanning Tree: %d\n", mstWeight);
}

// Function to implement Prim's algorithm
void prims(int graph[MAX][MAX], int n, int start) {
    int parent[MAX]; // Array to store the constructed MST
    int key[MAX];    // Key values used to pick minimum weight edge
    int mstSet[MAX]; // To represent set of vertices included in MST

    // Initialize all keys as infinite and mstSet[] as false
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Start from the given vertex
    key[start] = 0;     // Make key of start vertex 0 so that it is picked first
    parent[start] = -1; // Start vertex is the root of MST

    // The MST will have n vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum key vertex not yet included in MST
        int u = minKey(key, mstSet, n);

        // Add the picked vertex to the MST set
        mstSet[u] = 1;

        // Update key value and parent index of the adjacent vertices
        for (int v = 0; v < n; v++) {
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph, n);
}

int main() {
    int n, start;
    int graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use %d for infinity):\n", INT_MAX);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the start vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid start vertex.\n");
        return 1;
    }

    prims(graph, n, start);

    return 0;
}