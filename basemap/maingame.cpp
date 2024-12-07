#include "maingame.h"
#include "./Util/sort.h"
AdventureGame::AdventureGame() : health(100) {
    topics["1"] = "Standard Library Containers (map, vector, etc.)";
    topics["2"] = "Custom Template Class";
    topics["3"] = "Custom Namespace";
    topics["4"] = "Classes with Constructor, Destructor, Assignment Operator";
    topics["5"] = "Lambda Functions";
    topics["6"] = "Exception Handling";
    topics["7"] = "Inheritance";
    topics["8"] = "Virtual Functions or Abstract Classes";
    topics["9"] = "Hashing";
    topics["10"] = "Sorting Algorithms";
}

void AdventureGame::displayStats() const {
    std::cout << "Health: " << health << std::endl;
    std::cout << "Squares Completed: " << completedSquares << std::endl;
}

void AdventureGame::addItem(const std::string& item) {
    inventory.push_back(item);
    std::cout << "Added \"" << item << "\" to your inventory.\n";
    Util::quicksort<std::string>(inventory,0,inventory.size());

}

void AdventureGame::displayInventory() const {
    std::cout << "Inventory: ";
    if (inventory.empty()) {
        std::cout << "None\n";
    } else {
        for (const auto& item : inventory) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
}

void AdventureGame::displayTopics() const { 
    std::cout << "Available Maps:\n";
    for (const auto& topic : topics) {
        std::cout << topic.first << ": " << topic.second << "\n";
    }
}

bool AdventureGame::hasTopicsByID(std::string id) const {
    auto it = topics.find(id);
    if (it != topics.end()) {
        return true; 
    } else {
        return false; 
    }
}

void AdventureGame::displayTopicsByID(std::string id) const {
    auto it = topics.find(id);
    if (it != topics.end()) {
        std::cout << it->second << std::endl; 
    } else {
        return; 
    }
}

int AdventureGame::returnHealth() const {
    return health; 
}