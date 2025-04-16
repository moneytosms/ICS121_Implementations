#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int l, int h, int arr[])
{
    int pivot = arr[h]; // Use the last element as the pivot
    int i = l - 1;      // Index of the smaller element

    for (int j = l; j < h; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]); // Place the pivot in the correct position
    return i + 1;               // Return the partition index
}

void quicksort(int l, int h, int arr[])
{
    if (l < h)
    { // Base case: stop when l >= h
        int part = partition(l, h, arr);
        quicksort(l, part - 1, arr); // Sort the left subarray
        quicksort(part + 1, h, arr); // Sort the right subarray
    }
}

int main()
{
    int arr[] = {5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    quicksort(0, n - 1, arr);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

//time complexity:
//best case O(nlogn)
//average case O(nlogn)
//worst case O(n^2) if already sorted
//space complexity: O(logn) due to recursion