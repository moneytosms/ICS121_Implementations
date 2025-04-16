#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
    int size; // To keep track of the size of the stack
} Stack;

Stack *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int isEmpty(Stack *stack)
{
    return stack->size == 0;
}

int size(Stack *stack)
{
    return stack->size;
}

void push(Stack *stack, int data)
{
    Node *new_node = create_node(data);
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow\n");
        return -1;
    }
    Node *temp = stack->top;
    int popped_data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return popped_data;
}

int peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->top->data;
}

void print_stack(Stack *stack)
{
    Node *temp = stack->top;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void destroy_stack(Stack *stack)
{
    Node *temp = stack->top;
    while (temp != NULL)
    {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    free(stack);
}

void reverse(Stack *stack)
{
    if (isEmpty(stack))
        return;

    Node *prev = NULL, *current = stack->top, *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    stack->top = prev;
}

int contains(Stack *stack, int data)
{
    Node *temp = stack->top;
    while (temp != NULL)
    {
        if (temp->data == data)
            return 1; // Found
        temp = temp->next;
    }
    return 0; // Not found
}

void clear(Stack *stack)
{
    while (!isEmpty(stack))
    {
        pop(stack);
    }
}