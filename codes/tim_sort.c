#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform insertion sort on a subarray
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge function to merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;

    int* leftArr = (int*)malloc(len1 * sizeof(int));
    int* rightArr = (int*)malloc(len2 * sizeof(int));

    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

// Function to implement Tim Sort
void timSort(int arr[], int n) {
    int RUN = 32;  // Size of subarray to be sorted using insertion sort

    // Apply insertion sort to subarrays of size RUN
    for (int i = 0; i < n; i += RUN) {
        insertionSort(arr, i, (i + RUN - 1 < n - 1) ? (i + RUN - 1) : (n - 1));
    }

    // Start merging subarrays of size RUN
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n) ? (left + 2 * size - 1) : (n - 1);

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Driver function to test Tim Sort
int main() {
    int arr[] = {5, 21, 7, 23, 19, 4, 1, 9, 13, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    timSort(arr, n);

    printf("Sorted Array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
