#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int stack[MAX], top = -1;

void push(int value)
{
    stack[++top] = value;
}

int pop()
{
    return stack[top--];
}

bool isStackEmpty()
{
    return top == -1;
}

void DFS(int graph[MAX][MAX], int vertices, int start)
{
    bool visited[MAX] = {false};

    push(start);

    while (!isStackEmpty())
    {
        int current = pop();

        if (!visited[current])
        {
            printf("Visited %d\n", current);
            visited[current] = true;

            for (int i = vertices - 1; i >= 0; i--)
            { // Reverse for correct order
                if (graph[current][i] && !visited[i])
                {
                    push(i);
                }
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

    printf("DFS traversal starting from vertex 0:\n");
    DFS(graph, 5, 0);

    return 0;
}
