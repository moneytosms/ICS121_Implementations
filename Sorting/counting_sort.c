#include <stdio.h>
#include <stdlib.h>

void counting_sort(int arr[], int n)
{
    int max_num = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= max_num)
        {
            max_num = arr[i];
        }
    }

    int count_array[max_num + 1];
    for (int i = 0; i <= max_num; i++)
    {
        count_array[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        count_array[arr[i]] += 1;
    }

    int index = 0;
    for (int i = 0; i <= max_num; i++)
    {
        while (count_array[i] > 0)
        {
            arr[index] = i;
            index++;
            count_array[i]--;
        }
    }
}

int main()
{
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    counting_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}