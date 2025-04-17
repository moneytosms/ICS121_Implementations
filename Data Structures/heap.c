#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;

void initHeap(MaxHeap *heap) {
    heap->size = 0;
}

void heapifyUp(MaxHeap *heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->data[parent] < heap->data[index]) {
        int temp = heap->data[index];
        heap->data[index] = heap->data[parent];
        heap->data[parent] = temp;
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapifyDown(MaxHeap *heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    if (largest != index) {
        int temp = heap->data[index];
        heap->data[index] = heap->data[largest];
        heap->data[largest] = temp;
        heapifyDown(heap, largest);
    }
}

void insert(MaxHeap *heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap overflow\n");
        return;
    }

    heap->data[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;
}

int extractMax(MaxHeap *heap) {
    if (heap->size <= 0) {
        printf("Heap underflow\n");
        return -1;
    }

    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);

    return max;
}

void delete(MaxHeap *heap, int value) {
    int index = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Value not found in heap\n");
        return;
    }

    heap->data[index] = heap->data[heap->size - 1];
    heap->size--;

    heapifyDown(heap, index);
    heapifyUp(heap, index);
}

void printHeap(MaxHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    MaxHeap heap;
    initHeap(&heap);

    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 5);
    insert(&heap, 30);

    printf("Heap elements: ");
    printHeap(&heap);

    printf("Extracted max: %d\n", extractMax(&heap));
    printf("Heap after extraction: ");
    printHeap(&heap);

    delete(&heap, 20);
    printf("Heap after deleting 20: ");
    printHeap(&heap);

    return 0;
}
