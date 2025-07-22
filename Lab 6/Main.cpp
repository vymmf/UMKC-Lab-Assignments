#include <iostream>    // For input/output operations (std::cout, std::endl)
#include <vector>      // For std::vector (though C-style arrays are used as per assignment)
#include <algorithm>   // For std::swap
#include <chrono>      // For high-resolution time measurement
#include <random>      // For generating random numbers (std::random_device, std::mt19937, std::uniform_int_distribution)
#include <limits>      // For std::numeric_limits (used for clearing input buffer)

// The source of this code was from https://umsystem.instructure.com/courses/312246/files/folder/Labs/Sorting

// --- Utility Functions ---

/**
 * @brief Prints the elements of an integer array to standard output.
 * @param arr The integer array to print.
 * @param n The number of elements in the array.
 */
    void printArray(int arr[], int n) {
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

/**
 * @brief Populates an integer array with random values within a specified range.
 * @param arr The integer array to populate.
 * @param n The number of elements in the array.
 * @param minVal The minimum possible value for an element.
 * @param maxVal The maximum possible value for an element.
 */
    void generateRandomArray(int arr[], int n, int minVal, int maxVal) {
        // Seed the random number generator using a hardware-dependent source
        std::random_device rd;
        // Mersenne Twister engine for high-quality random numbers
        std::mt19937 gen(rd());
        // Distribution to generate integers within the specified range [minVal, maxVal]
        std::uniform_int_distribution<> distrib(minVal, maxVal);

        for (int i = 0; i < n; ++i) {
            arr[i] = distrib(gen);
        }
    }

/**
 * @brief Creates a deep copy of a source array into a destination array.
 * @param source The array to be copied from.
 * @param destination The array to be copied into.
 * @param n The number of elements to copy.
 */
    void copyArray(int source[], int destination[], int n) {
        for (int i = 0; i < n; ++i) {
            destination[i] = source[i];
        }
    }


// --- Sorting Algorithms Implementations ---

/**
 * @brief Sorts an integer array using the Selection Sort algorithm.
 * Time Complexity: O(n^2) in all cases.
 * Space Complexity: O(1)
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
    void selectionSort(int arr[], int n) {
        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i; // Assume the current element is the minimum
            // Find the minimum element in the unsorted part of the array
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[min_idx]) {
                    min_idx = j; // Update minimum index if a smaller element is found
                }
            }
            // Swap the found minimum element with the first element of the unsorted part
            std::swap(arr[i], arr[min_idx]);
        }
    }

/**
 * @brief Sorts an integer array using the Insertion Sort algorithm.
 * Time Complexity: O(n^2) average/worst, O(n) best (already sorted).
 * Space Complexity: O(1)
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
    void insertionSort(int arr[], int n) {
        for (int i = 1; i < n; ++i) {
            int key = arr[i]; // Current element to be inserted into the sorted part
            int j = i - 1;   // Index of the last element in the sorted part

            // Move elements of arr[0..i-1], that are greater than key,
            // to one position ahead of their current position
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key; // Place key at its correct position in sorted sub-array
        }
    }

/**
 * @brief Merges two sorted sub-arrays into a single sorted array.
 * Helper function for Merge Sort.
 * @param arr The main array containing the sub-arrays.
 * @param l The starting index of the first sub-array.
 * @param m The middle index (end of first sub-array, start-1 of second).
 * @param r The ending index of the second sub-array.
 */
    void merge(int arr[], int l, int m, int r) {
        int n1 = m - l + 1; // Size of the first sub-array
        int n2 = r - m;     // Size of the second sub-array

        // Create temporary arrays to hold the sub-arrays
        int* L = new int[n1];
        int* R = new int[n2];

        // Copy data to temp arrays L[] and R[]
        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        // Merge the temp arrays back into arr[l..r]
        int i = 0; // Initial index of first sub-array
        int j = 0; // Initial index of second sub-array
        int k = l; // Initial index of merged sub-array

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[], if any
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R[], if any
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        // Deallocate dynamically allocated memory for temporary arrays
        delete[] L;
        delete[] R;
    }

/**
 * @brief Sorts an integer array using the Merge Sort algorithm.
 * Time Complexity: O(n log n) in all cases.
 * Space Complexity: O(n) due to temporary arrays in merge function.
 * @param arr The array to be sorted.
 * @param l The starting index of the sub-array to be sorted.
 * @param r The ending index of the sub-array to be sorted.
 */
    void mergeSort(int arr[], int l, int r) {
        if (l < r) {
            // Find the middle point to divide the array into two halves
            int m = l + (r - l) / 2; // Avoids overflow for large l and r

            // Recursively sort the first and second halves
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);

            // Merge the sorted halves
            merge(arr, l, m, r);
        }
    }

/**
 * @brief Partitions the array around a pivot element.
 * Helper function for Quick Sort.
 * @param arr The array to be partitioned.
 * @param low The starting index of the sub-array to be partitioned.
 * @param high The ending index of the sub-array to be partitioned (pivot element).
 * @return The index of the pivot element after partitioning.
 */
    int partition(int arr[], int low, int high) {
        int pivot = arr[high]; // Choose the last element as the pivot
        int i = (low - 1);     // Index of smaller element

        for (int j = low; j <= high - 1; j++) {
            // If current element is smaller than or equal to pivot
            if (arr[j] < pivot) {
                i++; // Increment index of smaller element
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]); // Place the pivot at its correct sorted position
        return (i + 1); // Return the pivot's final index
    }

/**
 * @brief Sorts an integer array using the Quick Sort algorithm.
 * Time Complexity: O(n log n) average, O(n^2) worst (unbalanced partitions).
 * Space Complexity: O(log n) for recursion stack.
 * @param arr The array to be sorted.
 * @param low The starting index of the sub-array to be sorted.
 * @param high The ending index of the sub-array to be sorted.
 */
    void quickSort(int arr[], int low, int high) {
        if (low < high) {
            // pi is partitioning index, arr[pi] is now at right place
            int pi = partition(arr, low, high);

            // Recursively sort elements before partition and after partition
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

/**
 * @brief Sorts an integer array using the Bubble Sort algorithm.
 * Time Complexity: O(n^2) average/worst, O(n) best (already sorted with optimization).
 * Space Complexity: O(1)
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
    void bubbleSort(int arr[], int n) {
        bool swapped; // Optimization: If no two elements were swapped by inner loop, then array is sorted
        for (int i = 0; i < n - 1; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) { // Last i elements are already in place
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            // If no two elements were swapped by inner loop, then break
            if (swapped == false) {
                break;
            }
        }
    }


// --- Main Function for Testing and Comparison ---

    int main() {
        // Define the size of the array for testing.
        // Adjust this value to test performance with different data scales.
        const int ARRAY_SIZE = 50000; // Example: 10000, 50000, 100000
        // Dynamic allocation for potentially large arrays to avoid stack overflow
        int* originalArray = new int[ARRAY_SIZE];
        int* tempArray = new int[ARRAY_SIZE]; // Temporary array for copying before each sort

        // Seed the random number generator and populate the original array
        // Values between 1 and 1,000,000
        generateRandomArray(originalArray, ARRAY_SIZE, 1, 1000000);

        std::cout << "--- Sorting Algorithms Performance Comparison ---\n";
        std::cout << "Array Size: " << ARRAY_SIZE << " elements\n\n";

        // --- Test Selection Sort ---
        copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
        auto start_sel = std::chrono::high_resolution_clock::now();
        selectionSort(tempArray, ARRAY_SIZE);
        auto end_sel = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_sel = end_sel - start_sel;
        std::cout << "Selection Sort Time: " << duration_sel.count() << " seconds\n";
        // For very small arrays (e.g., ARRAY_SIZE < 20), you could uncomment printArray:
        // std::cout << "Sorted Array (Selection Sort): "; printArray(tempArray, ARRAY_SIZE);


        // --- Test Insertion Sort ---
        copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
        auto start_ins = std::chrono::high_resolution_clock::now();
        insertionSort(tempArray, ARRAY_SIZE);
        auto end_ins = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_ins = end_ins - start_ins;
        std::cout << "Insertion Sort Time: " << duration_ins.count() << " seconds\n";

        // --- Test Merge Sort ---
        copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
        auto start_merge = std::chrono::high_resolution_clock::now();
        mergeSort(tempArray, 0, ARRAY_SIZE - 1);
        auto end_merge = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_merge = end_merge - start_merge;
        std::cout << "Merge Sort Time:   " << duration_merge.count() << " seconds\n"; // Added spaces for alignment

        // --- Test Quick Sort ---
        copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
        auto start_quick = std::chrono::high_resolution_clock::now();
        quickSort(tempArray, 0, ARRAY_SIZE - 1);
        auto end_quick = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_quick = end_quick - start_quick;
        std::cout << "Quick Sort Time:   " << duration_quick.count() << " seconds\n"; // Added spaces for alignment

        // --- Test Bubble Sort ---
        // Note: Bubble Sort is extremely slow for large arrays.
        // If ARRAY_SIZE is very large (e.g., > 10,000), it might take a very long time.
        copyArray(originalArray, tempArray, ARRAY_SIZE); // Ensure fresh data
        auto start_bubble = std::chrono::high_resolution_clock::now();
        bubbleSort(tempArray, ARRAY_SIZE);
        auto end_bubble = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_bubble = end_bubble - start_bubble;
        std::cout << "Bubble Sort Time:  " << duration_bubble.count() << " seconds\n"; // Added spaces for alignment

        std::cout << "\n--- End of Comparison ---\n";

        // Clean up dynamically allocated memory
        delete[] originalArray;
        delete[] tempArray;

        return 0;
    }