#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

List* create_list() {
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    return list;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node* insert(List* list){
    int data;
    printf("Enter data to insert: ");
    scanf("%d", &data);
    Node* new_node = create_node(data);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    return list->head;
}

int locate(List* list, int data) {
    Node* temp = list->head;
    int index = 0;
    while (temp != NULL) {
        if (temp->data == data) {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1; // Not found
}

int retrieve(List* list, int index) {
    Node* temp = list->head;
    int count = 0;
    while (temp != NULL) {
        if (count == index) {
            return temp->data;
        }
        temp = temp->next;
        count++;
    }
    return -1; // Invalid index
}

void delete_index(List* list, int index) {
    if (list->head == NULL) {
        return; // List is empty
    }
    Node* temp = list->head;
    if (index == 0) {
        list->head = temp->next;
        free(temp);
        return;
    }
    for (int i = 0; i < index - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        return; // Invalid index
    }
    Node* next_node = temp->next->next;
    free(temp->next);
    temp->next = next_node;
}

void delete_data(List* list, int data){
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return; // Data not found
    }
    if (prev == NULL) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

void print_list(List* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void destroy_list(List* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}

int main() {
    int choice, index, value;
    List* list = NULL;

    while (1) {
        printf("1. Create List\n");
        printf("2. Insert Element\n");
        printf("3. Locate Element\n");
        printf("4. Retrieve Element\n");
        printf("5. Delete Element by Index\n");
        printf("6. Print List\n");
        printf("7. Destroy List\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list = create_list();
                printf("List created.\n");
                break;
            case 2:
                if (list == NULL) {
                    printf("Create a list first.\n");
                    break;
                }
                insert(list);
                break;
            case 3:
                if (list == NULL) {
                    printf("Create a list first.\n");
                    break;
                }
                printf("Enter value to locate: ");
                scanf("%d", &value);
                index = locate(list, value);
                if (index == -1) {
                    printf("Value not found.\n");
                } else {
                    printf("Value found at index %d.\n", index);
                }
                break;
            case 4:
                if (list == NULL) {
                    printf("Create a list first.\n");
                    break;
                }
                printf("Enter index to retrieve: ");
                scanf("%d", &index);
                value = retrieve(list, index);
                if (value == -1) {
                    printf("Invalid index.\n");
                } else {
                    printf("Value at index %d is %d.\n", index, value);
                }
                break;
            case 5:
                if (list == NULL) {
                    printf("Create a list first.\n");
                    break;
                }
                printf("Enter index to delete: ");
                scanf("%d", &index);
                delete_index(list, index);
                break;
            case 6:
                if (list == NULL) {
                    printf("Create a list first.\n");
                    break;
                }
                print_list(list);
                break;
            case 7:
                if (list == NULL) {
                    printf("No list to destroy.\n");
                    break;
                }
                destroy_list(list);
                list = NULL;
                printf("List destroyed.\n");    
                break;
            case 8:
                if (list != NULL) {
                    destroy_list(list);
                }
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}