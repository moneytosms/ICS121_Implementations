#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in BST
Node *insert(Node *root, int data)
{
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Function to search for a node in BST
void search(Node *root, int data)
{
    if (root == NULL)
    {
        printf("Node not found\n");
        return;
    }
    if (root->data == data)
    {
        printf("Node found: %d\n", root->data);
        return;
    }
    if (data < root->data)
        search(root->left, data);
    else
        search(root->right, data);
}

// Function to find the minimum value node
Node *minimum(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

// Function to find the maximum value node
Node *maximum(Node *root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;
}

// Function to delete a node from BST
Node *deleteNode(Node *root, int data)
{
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else
    {
        // Node with only one child or no child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: get the inorder successor
        Node *temp = minimum(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
        free(temp);
    }
    return root;
}

// Function to find the inorder successor of a given node
void inorderSuccessor(Node *root, int data)
{
    Node *current = root;
    Node *successor = NULL;

    while (current != NULL)
    {
        if (data < current->data)
        {
            successor = current;
            current = current->left;
        }
        else if (data > current->data)
        {
            current = current->right;
        }
        else
        {
            if (current->right != NULL)
            {
                successor = minimum(current->right);
            }
            break;
        }
    }

    if (successor)
        printf("Inorder Successor: %d\n", successor->data);
    else
        printf("No Inorder Successor\n");
}

// Function to find the inorder predecessor of a given node
void inorderPredecessor(Node *root, int data)
{
    Node *current = root;
    Node *predecessor = NULL;

    while (current != NULL)
    {
        if (data > current->data)
        {
            predecessor = current;
            current = current->right;
        }
        else if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            if (current->left != NULL)
            {
                predecessor = maximum(current->left);
            }
            break;
        }
    }

    if (predecessor)
        printf("Inorder Predecessor: %d\n", predecessor->data);
    else
        printf("No Inorder Predecessor\n");
}

// Function to print tree in inorder traversal
void inorder(Node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Function to print the tree structure
void printTree(Node *root, int space)
{
    if (root == NULL)
        return;

    space += 10;
    printTree(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    printTree(root->left, space);
}

// Function to free memory allocated for the BST
void freeTree(Node *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main function to test the optimized BST
int main()
{
    Node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    search(root, 40);
    search(root, 100);

    inorderSuccessor(root, 50);
    inorderPredecessor(root, 50);

    root = deleteNode(root, 50);

    printf("Inorder Traversal after deleting 50: ");
    inorder(root);
    printf("\n");

    printTree(root, 0);

    freeTree(root);
    return 0;
}
