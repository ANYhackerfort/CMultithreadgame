#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
#include "../Util/sort.h"

template <typename T>
class Inventory {
private:
    struct Node {
        std::string key;
        T value;
        int count;
    };

    size_t inventorySize;
    std::vector<std::list<Node>> inventoryHashMap;

    size_t hashFunction(const std::string& key) const;

public:
    Inventory(size_t size = 10);

    void addItem(const std::string& key, const T& value);

    void removeItem(const std::string& key);

    T* getItem(const std::string& key);

    void displayItems() const;

    std::vector<std::string> sortItemsIntoArrayName() const;

    std::vector<int> sortItemsIntoArrayCount() const;
};

// Constructor
template <typename T>
Inventory<T>::Inventory(size_t size) : inventorySize(size), inventoryHashMap(size) {}

// Hash Function
template <typename T>
size_t Inventory<T>::hashFunction(const std::string& key) const {
    std::hash<std::string> hasher;
    return hasher(key) % inventorySize;
}

// Add Item
template <typename T>
void Inventory<T>::addItem(const std::string& key, const T& value) {
    std::cout << "Added [" << key << "] to your inventory!" << std::endl;
    size_t index = hashFunction(key);
    for (auto& node : inventoryHashMap[index]) {
        if (node.key == key) {
            node.count += 1;
            return;
        }
    }
    inventoryHashMap[index].push_back({key, value, 1});
}

// Remove Item
template <typename T>
void Inventory<T>::removeItem(const std::string& key) {
    size_t index = hashFunction(key);
    auto& bucket = inventoryHashMap[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->key == key) {
            if (it->count <= 1) {
                bucket.erase(it);
            } else {
                it->count--;
            }
            return;
        }
    }
}

// Get Item
template <typename T>
T* Inventory<T>::getItem(const std::string& key) {
    size_t index = hashFunction(key);
    for (auto& node : inventoryHashMap[index]) {
        if (node.key == key) {
            return &node.value;
        }
    }
    return nullptr;
}

// Display Items
template <typename T>
void Inventory<T>::displayItems() const {
    for (const auto& bucket : inventoryHashMap) {
        for (const auto& node : bucket) {
            std::cout << "Item Name: " << node.key << " || You have " << node.count << " of these!" << std::endl;
        }
    }
}

// Sort Items by Name
template <typename T>
std::vector<std::string> Inventory<T>::sortItemsIntoArrayName() const {
    std::vector<std::string> items;
    for (const auto& bucket : inventoryHashMap) {
        for (const auto& node : bucket) {
            items.push_back(node.key);
        }
    }
    Util::quicksort<std::string>(items, 0, items.size() - 1); // Use actual size
    return items;
}

// Sort Items by Count
template <typename T>
std::vector<int> Inventory<T>::sortItemsIntoArrayCount() const {
    std::vector<int> counts;
    for (const auto& bucket : inventoryHashMap) {
        for (const auto& node : bucket) {
            counts.push_back(node.count);
        }
    }
    Util::quicksort<int>(counts, 0, counts.size() - 1); // Use actual size
    return counts;
}

#endif // INVENTORY_H
