#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void insertion_sort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to get high-precision time in seconds
LARGE_INTEGER get_time()
{
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return time;
}

// Function to calculate elapsed time
double elapsed_time(LARGE_INTEGER start, LARGE_INTEGER end, LARGE_INTEGER frequency)
{
    return (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency); // Get CPU timer frequency
    start = get_time();                    // Start timing

    insertion_sort(arr, n);

    end = get_time(); // End timing

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Time taken for sorting: %.12f seconds\n", elapsed_time(start, end, frequency));

    free(arr);
    return 0;
}
