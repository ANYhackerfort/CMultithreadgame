#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>
#include <functional>
#include "../GameEntities/gameItem.h"
 
namespace Util {
    template <typename T>
    int partition(std::vector<T>& arr, int low, int high, const std::function<bool(const T&, const T&)>& comparator) {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (comparator(arr[j], pivot)) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template <typename T>
    void quicksort(std::vector<T>& arr, int low, int high, const std::function<bool(const T&, const T&)>& comparator) {
        if (low < high) {
            int pi = partition(arr, low, high, comparator);
            quicksort(arr, low, pi - 1, comparator);
            quicksort(arr, pi + 1, high, comparator);
        }
    }

    template <typename T = std::shared_ptr<GameItem>>
    struct Node {
        std::string key;
        T value;
        int count;
    };

    template <typename T>
    void quicksort(std::vector<Node<T>>& arr, int low, int high, const std::string& byWhat) {
        std::function<bool(const Node<T>&, const Node<T>&)> comparator;

        if (byWhat == "count") {
            comparator = [](const Node<T>& a, const Node<T>& b) {
                return a.count < b.count; 
            };
        } else if (byWhat == "name") {
            comparator = [](const Node<T>& a, const Node<T>& b) {
                return a.key < b.key; 
            };
        } else {
            throw std::invalid_argument("Invalid sort criteria: " + byWhat);
        }

        quicksort(arr, low, high, comparator);
    }
}

#endif
