#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *arr;
    int size;
} List;

List* create_list(int size) {
    List *list = (List *)malloc(sizeof(List));
    list->arr = (int *)malloc(size * sizeof(int));
    list->size = size;
    return list;
}

void insert(List* l, int n, int val) {
    l->arr[n] = val;
}

int locate(List *l, int val){
    for (int i = 0; i < l->size; i++) {
        if (l->arr[i] == val) {
            return i;
        }
    }
    return -1; // Not found
}

int retrieve(List *l, int n) {
    if (n < 0 || n >= l->size) {
        return -1; // Invalid index
    }
    return l->arr[n];
}

void delete(List *l, int n) {
    if (n < 0 || n >= l->size) {
        return; // Invalid index
    }
    for (int i = n; i < l->size - 1; i++) {
        l->arr[i] = l->arr[i + 1];
    }
    l->size--;
}

void print_list(List *l) {
    for (int i = 0; i < l->size; i++) {
        printf("%d ", l->arr[i]);
    }
    printf("\n");
}

void destroy_list(List *l) {
    free(l->arr);
    free(l);
}

int main() {
    int choice, size, index, value;
    List *list = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create List\n");
        printf("2. Insert Element\n");
        printf("3. Locate Element\n");
        printf("4. Retrieve Element\n");
        printf("5. Delete Element\n");
        printf("6. Print List\n");
        printf("7. Destroy List\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (list != NULL) {
                    printf("List already exists. Destroy it first.\n");
                    break;
                }
                printf("Enter size of the list: ");
                scanf("%d", &size);
                list = create_list(size);
                printf("List created with size %d.\n", size);
                break;

            case 2:
                if (list == NULL) {
                    printf("Create a list first.\n");
                    break;
                }
                printf("Enter index and value to insert: ");
                scanf("%d %d", &index, &value);
                if (index < 0 || index >= list->size) {
                    printf("Invalid index.\n");
                } else {
                    insert(list, index, value);
                    printf("Inserted %d at index %d.\n", value, index);
                }
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
                if (index < 0 || index >= list->size) {
                    printf("Invalid index.\n");
                } else {
                    delete(list, index);
                    printf("Deleted element at index %d.\n", index);
                }
                break;

            case 6:
                if (list == NULL) {
                    printf("Create a list first.\n");
                    break;
                }
                printf("List elements: ");
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
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}