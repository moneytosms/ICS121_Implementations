#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int queue[MAX], front = 0, rear = 0;

void enqueue(int value)
{
    queue[rear++] = value;
}

int dequeue()
{
    return queue[front++];
}

bool isQueueEmpty()
{
    return front == rear;
}

void BFS(int graph[MAX][MAX], int vertices, int start)
{
    bool visited[MAX] = {false};

    enqueue(start);
    visited[start] = true;

    while (!isQueueEmpty())
    {
        int current = dequeue();
        printf("Visited %d\n", current);

        for (int i = 0; i < vertices; i++)
        {
            if (graph[current][i] && !visited[i])
            {
                enqueue(i);
                visited[i] = true;
            }
        }
    }
}

int main()
{
    int graph[MAX][MAX] = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}};

    printf("BFS traversal starting from vertex 0:\n");
    BFS(graph, 5, 0);

    return 0;
}
