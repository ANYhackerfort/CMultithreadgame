#include "maingame.h"
#include "./Util/sort.h"
#include "./GameEntities/inventory.h"
#include "./GameEntities/gameItem.h"

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

void AdventureGame::addItem(std::string& name, std::shared_ptr<GameItem> item) {
    inventory.addItem(name, item);
}

void AdventureGame::displayInventory(std::string type) const {
    inventory.displayItems(type); 
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

void AdventureGame::useItemByName(std::string name) {
    if(inventory.healWithItem(name, health)) {
        std::cout << "You just used: " << name << " and healed you to [" << health << "]" << std::endl; 
        inventory.removeItem(name);
    } else {
        std::cout << "You do not have this item!" << std::endl;
    }
    
}