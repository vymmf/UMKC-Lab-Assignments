#include <iostream>    // For input/output operations (cout, endl)
#include <vector>      // For vector (though C-style arrays are used as per assignment)
#include <algorithm>   // For wap
#include <chrono>      // For high-resolution time measurement
#include <random>      // For generating random numbers (random_device, mt19937, uniform_int_distribution)
#include <limits>      // For numeric_limits (used for clearing input buffer)

using namespace std;

// The source of this code was from https://umsystem.instructure.com/courses/312246/files/folder/Labs/Sorting

void printArray(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void generateRandomArray(int arr[], int len, int minVal = 1, int maxVal = 1000000) {
    // Seed the random number generator using a hardware-dependent source
    random_device rd;
    // Mersenne Twister engine for high-quality random numbers
    mt19937 gen(rd());
    // Distribution to generate integers within the specified range [minVal, maxVal]
    uniform_int_distribution<> distrib(minVal, maxVal);

    for (int i = 0; i < len; ++i) {
        arr[i] = distrib(gen);
    }
}

void copyArray(int source[], int destination[], int len) {
    for (int i = 0; i < len; ++i) {
        destination[i] = source[i];
    }
}

void selectionSort(int arr[], int len) {
    for (int i = 0; i < len - 1; ++i) {
        int min_idx = i;
        // Redefines the minimum index in each iteration, unless the current index is the minimum index
        for (int j = i + 1; j < len; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element of the unsorted part
        swap(arr[i], arr[min_idx]);
    }
}

void insertionSort(int arr[], int len) {
    for (int i = 1; i < len; ++i) {
        int key = arr[i]; // Current element that is to be sorted
        int j = i - 1;   // Index of the last element that was sorted (Default should be 0)

        // Move elements in the array greater than key to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // Place key at its correct position in sorted sub-array
    }
}

void merge(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1; // Size of the first sub-array
    int len2 = right - mid;     // Size of the second sub-array

    // Create temporary arrays to hold the sub-arrays
    int* Left = new int[len1];
    int* Right = new int[len2];

    // Copy data to temp arrays Left[] and Right[]
    for (int i = 0; i < len1; i++)
        Left[i] = arr[left + i];
    for (int j = 0; j < len2; j++)
        Right[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left,...,right]
    int i = 0; // Initial index of first sub-array
    int j = 0; // Initial index of second sub-array
    int k = left; // Initial index of merged sub-array

    while (i < len1 && j < len2) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        }
        else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of Left[], if any
    while (i < len1) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of Right[], if any
    while (j < len2) {
        arr[k] = Right[j];
        j++;
        k++;
    }

    // Deallocate dynamically allocated memory for temporary arrays
    delete[] Left;
    delete[] Right;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find the middle point to divide the array into two halves
        int mid = left + (right - left) / 2; // Avoids overflow for large ints

        // Recursively sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] < pivot) {
            i++; // Increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Place the pivot at its correct sorted position
    return (i + 1); // Return the pivot's final index
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Recursively sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bubbleSort(int arr[], int len) {
    bool swapped; // Optimization: If no two elements were swapped by inner loop, then array is sorted
    for (int i = 0; i < len - 1; ++i) {
        swapped = false;
        for (int j = 0; j < len - i - 1; ++j) { // Last i elements are already in place
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped by inner loop, then break
        if (!swapped) {
            break;
        }
    }
}

int main() {
    const int ARRAY_SIZE = 50000;
    int* originalArray = new int[ARRAY_SIZE];
    int* tempArray = new int[ARRAY_SIZE];

    generateRandomArray(originalArray, ARRAY_SIZE);

    cout << "--- Sorting Algorithms Performance Comparison ---\n";
    cout << "Array Size: " << ARRAY_SIZE << " elements\n\n";

    // --- Test Selection Sort ---
    copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
    auto start_sel = chrono::high_resolution_clock::now();
    selectionSort(tempArray, ARRAY_SIZE);
    auto end_sel = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_sel = end_sel - start_sel;
    cout << "Selection Sort Time: " << duration_sel.count() << " seconds\n";
   //  cout << "Sorted Array (Selection Sort): "; printArray(tempArray, ARRAY_SIZE);


    // --- Test Insertion Sort ---
    copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
    auto start_ins = chrono::high_resolution_clock::now();
    insertionSort(tempArray, ARRAY_SIZE);
    auto end_ins = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_ins = end_ins - start_ins;
    cout << "Insertion Sort Time: " << duration_ins.count() << " seconds\n";

    // --- Test Merge Sort ---
    copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
    auto start_merge = chrono::high_resolution_clock::now();
    mergeSort(tempArray, 0, ARRAY_SIZE - 1);
    auto end_merge = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_merge = end_merge - start_merge;
    cout << "Merge Sort Time:   " << duration_merge.count() << " seconds\n";

    // --- Test Quick Sort ---
    copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
    auto start_quick = chrono::high_resolution_clock::now();
    quickSort(tempArray, 0, ARRAY_SIZE - 1);
    auto end_quick = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_quick = end_quick - start_quick;
    cout << "Quick Sort Time:   " << duration_quick.count() << " seconds\n";

    // --- Test Bubble Sort ---
    copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
    auto start_bubble = chrono::high_resolution_clock::now();
    bubbleSort(tempArray, ARRAY_SIZE);
    auto end_bubble = chrono::high_resolution_clock::now();
    chrono::duration<double> duration_bubble = end_bubble - start_bubble;
    cout << "Bubble Sort Time:  " << duration_bubble.count() << " seconds\n";

    cout << "\n--- End of Comparison ---\n";

    // Clean up dynamically allocated memory
    delete[] originalArray;
    delete[] tempArray;

    return 0;
}