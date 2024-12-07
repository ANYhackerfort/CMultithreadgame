#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include <iostream>
#include <vector>
#include <memory>

class GameItem {
private:
    int data;

public:
    GameItem(int d) : data(d) {}

    virtual ~GameItem() = default; 

    int getData() const { return data; }
    void setData(int d) { data = d; }

    virtual void healPlayer(int& health) const {
        std::cout << "WHAT";
        return;};
};

// Derived classes
class SmallHealthPotion : public GameItem {
public:
    SmallHealthPotion() : GameItem(10) {}

    void healPlayer(int& health) const override {
        health += getData();
    }
};

class HealthPotion : public GameItem {
public:
    HealthPotion() : GameItem(20) {}

    void healPlayer(int& health) const override {
        std::cout << "HEsdfsdfLLO";
        health += getData();
    }
};

class BigHealthPotion : public GameItem {
public:
    BigHealthPotion() : GameItem(40) {}

    void healPlayer(int& health) const override {
        health += getData();
    }
};

class Apple : public GameItem {
public:
    Apple() : GameItem(1) {}

    void healPlayer(int& health) const override {
        health += getData();
    }
};

#endif
