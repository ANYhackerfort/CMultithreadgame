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
    int health;
    Inventory<GameItem> inventory;
    std::unordered_map<std::string, std::string> topics;

public:
    int completedSquares = 0; //im too lazy
    AdventureGame();
    virtual ~AdventureGame() {}

    int returnHealth() const; 
    void displayStats() const;
    void addItem(std::string& name, GameItem& item); 

    void displayInventory () const; 

    void displayTopics() const;

    bool hasTopicsByID(std::string id) const; 
    void displayTopicsByID(std::string id) const; 

};

#endif // ADVENTURE_GAME_H
