#include <stdio.h>
#include <stdlib.h>

void prn(int n, int m[][50])
{
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (m[i][j] == 999)
                printf("∞\t"); // for clarity
            else
                printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(int n, int s, int m[][50], int dist[50])
{
    int visited[50] = {0};

    for (int i = 0; i < n; i++)
    {
        dist[i] = m[s][i];
    }
    visited[s] = 1;
    dist[s] = 0;

    for (int count = 1; count < n; count++)
    {
        int min = 999, v = -1;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                min = dist[i];
                v = i;
            }
        }

        if (v == -1)
            break; // All reachable nodes are visited

        visited[v] = 1;

        for (int i = 0; i < n; i++)
        {
            if (m[v][i] != 999 && dist[i] > dist[v] + m[v][i])
            {
                dist[i] = dist[v] + m[v][i];
            }
        }
    }
}

int main()
{
    int n, s, m[50][50], dist[50];

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge, non-zero weight for edge):\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Edge %d -> %d: ", i, j);
            scanf("%d", &m[i][j]);
        }
    }

    // Replace 0s with 999 (except diagonal)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && m[i][j] == 0)
            {
                m[i][j] = 999;
            }
        }
    }

    prn(n, m);

    printf("Enter source node (0 to %d): ", n - 1);
    scanf("%d", &s);

    dijkstra(n, s, m, dist);

    printf("Shortest paths from node %d:\n", s);
    for (int i = 0; i < n; i++)
    {
        if (s != i)
        {
            printf("%d -> %d = %d\n", s, i, dist[i]);
        }
    }

    return 0;
}
