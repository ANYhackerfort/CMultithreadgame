#ifndef ADVENTURE_GAME_H
#define ADVENTURE_GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "./GameEntities/inventory.h"
#include "./GameEntities/gameItem.h"

class AdventureGame {
protected:
    Inventory<GameItem> inventory;
    std::unordered_map<std::string, std::string> topics;

public:
    int health;
    int completedSquares = 0;

public:
    AdventureGame();
    virtual ~AdventureGame() {}

    int returnHealth() const; 
    void displayStats() const;
    void addItem(std::string& name, std::shared_ptr<GameItem> item);

    void displayInventory (std::string type = "") const; 

    void displayTopics() const;

    bool hasTopicsByID(std::string id) const; 
    void displayTopicsByID(std::string id) const; 
    
    void useItemByName(std::string name);
};

#endif
