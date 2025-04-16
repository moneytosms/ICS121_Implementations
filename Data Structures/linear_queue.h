#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
    int size;
} Queue;

Queue *create_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int is_empty(Queue *queue)
{
    return queue->size == 0;
}

int queue_size(Queue *queue)
{
    return queue->size;
}

void enqueue(Queue *queue, int data)
{
    Node *new_node = create_node(data);
    if (queue->rear == NULL)
    {
        queue->front = queue->rear = new_node;
    }
    else
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

int dequeue(Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue underflow\n");
        return -1;
    }
    Node *temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    queue->size--;
    return data;
}

int front(Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->front->data;
}

void print_queue(Queue *queue)
{
    Node *temp = queue->front;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void destroy_queue(Queue *queue)
{
    Node *temp = queue->front;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(queue);
}

void clear(Queue *queue)
{
    while (!is_empty(queue))
    {
        dequeue(queue);
    }
}
