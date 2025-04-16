#include <stdio.h>
#include <stdlib.h>

// Function to get the maximum value in the array
int get_max(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// Counting sort for a specific digit represented by exp
void counting_sort_for_radix(int arr[], int n, int exp)
{
    int output[n];       // Output array
    int count[10] = {0}; // Count array for digits (0-9)

    // Count occurrences of each digit
    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int digit = (arr[i] / exp) % 10;
        output[--count[digit]] = arr[i];
    }

    // Copy the output array back to arr[]
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

// Radix Sort function
void radix_sort(int arr[], int n)
{
    int max = get_max(arr, n);

    // Perform counting sort for each digit (1s, 10s, 100s, etc.)
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort_for_radix(arr, n, exp);
    }
}

int main()
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    radix_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}