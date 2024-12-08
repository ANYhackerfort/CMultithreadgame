#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "../Util/sort.h"

template <typename T>
class Inventory {
private:
    std::size_t inventorySize;
    std::vector<std::list<Util::Node<std::shared_ptr<T>>>> inventoryHashMap;
    std::size_t numItems;

    size_t hashFunction(const std::string& key) const;

public:
    Inventory(size_t size = 10);

    void addItem(const std::string& key, const std::shared_ptr<T>& value);

    void removeItem(const std::string& key);

    std::shared_ptr<T> getItem(const std::string& key);

    void displayItems(std::string type = "") const;

    void displaySortItemsIntoArrayName() const;
    void displaySortItemsIntoArrayCount() const;

    bool healWithItem(const std::string& key, int& health);
    Inventory<T>& operator=(const Inventory<T>& other); 
};

template <typename T>
Inventory<T>::Inventory(size_t size)
    : inventorySize(size), inventoryHashMap(size), numItems(0) {} //sets up inventorysizeof10

template <typename T>
Inventory<T>& Inventory<T>::operator=(const Inventory<T>& other) {
    if (this == &other) {
        return this;
    }

    inventorySize = other.inventorySize;
    numItems = other.numItems;
    inventoryHashMap.clear();
    inventoryHashMap.resize(other.inventorySize);

    for (size_t i = 0; i < other.inventoryHashMap.size(); ++i) {
        for (const auto& node : other.inventoryHashMap[i]) {
            inventoryHashMap[i].emplace_back(node);
        }
    }
    return *this;
}

template <typename T>
size_t Inventory<T>::hashFunction(const std::string& key) const {
    std::hash<std::string> hasher;
    return hasher(key) % inventorySize;
}

template <typename T>
void Inventory<T>::addItem(const std::string& key, const std::shared_ptr<T>& value) {
    std::cout << "Added [" << key << "] to your inventory!" << std::endl;
    size_t index = hashFunction(key);
    for (auto& node : inventoryHashMap[index]) {
        if (node.key == key) {
            node.count += 1;
            return;
        }
    }
    inventoryHashMap[index].push_back({key, value, 1});
    numItems++;
}

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
            numItems--;
            return;
        }
    }
}

template <typename T>
std::shared_ptr<T> Inventory<T>::getItem(const std::string& key) {
    size_t index = hashFunction(key);
    for (auto& node : inventoryHashMap[index]) {
        if (node.key == key) {
            return node.value;
        }
    }
    return nullptr;
}

template <typename T>
bool Inventory<T>::healWithItem(const std::string& key, int& health) {
    auto item = getItem(key);
    if (item) {
        item->healPlayer(health);
        return true;
    } else {
        return false;
    }
}

template <typename T>
void Inventory<T>::displayItems(std::string type) const {
    if (numItems == 0) {
        std::cout << "You don't currently have any items in your Inventory!" << std::endl;
    } else if (type == "") {
        for (const auto& bucket : inventoryHashMap) {
            for (const auto& node : bucket) {
                std::cout << "Item Name: " << node.key << " || You have " << node.count << " of these!" << std::endl;
            }
        }
    } else if (type == "name") {
        displaySortItemsIntoArrayName();
    } else if (type == "count") {
        displaySortItemsIntoArrayCount();
    }
}

template <typename T>
void Inventory<T>::displaySortItemsIntoArrayName() const {
    std::vector<Util::Node<std::shared_ptr<T>>> items;
    for (const auto& bucket : inventoryHashMap) {
        for (const auto& node : bucket) {
            items.push_back(node);
        }
    }
    Util::quicksort(items, 0, numItems - 1, "name");
    for (const auto& node : items) {
        std::cout << "Item Name: " << node.key << " || You have " << node.count << " of these!" << std::endl;
    }
}

template <typename T>
void Inventory<T>::displaySortItemsIntoArrayCount() const {
    std::vector<Util::Node<std::shared_ptr<T>>> items;
    for (const auto& bucket : inventoryHashMap) {
        for (const auto& node : bucket) {
            items.push_back(node);
        }
    }
    Util::quicksort(items, 0, items.size() - 1, "count");
    for (const auto& node : items) {
        std::cout << "Item Name: " << node.key << " || You have " << node.count << " of these!" << std::endl;
    }
}

#endif
