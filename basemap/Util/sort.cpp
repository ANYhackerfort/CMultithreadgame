#include <iostream>
#include <vector>
#include <algorithm> // for std::swap

// Template Partition function
template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[high]; 
    int i = low - 1; 

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) { 
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}


template <typename T>
void quicksort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}
