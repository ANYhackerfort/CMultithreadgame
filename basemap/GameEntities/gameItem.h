#ifndef GAME_ITEM_H
#define GAME_ITEM_H

class GameItem {
private:
    int data; 

public:

    GameItem(int d) : data(d) {}
    
    GameItem& operator=(const GameItem& other) {
        if (this != &other) {
            this->data = other.data; 
        }
        return *this; 
    }

    int getData() const { return data; }


    void setData(int d) { data = d; }
};


class SmallHealthPotion : public GameItem {
public:
    SmallHealthPotion() : GameItem(10) {} 
};

class HealthPotion : public GameItem {
public:
    HealthPotion() : GameItem(20) {} 
};

class BigHealthPotion : public GameItem {
public:
    BigHealthPotion() : GameItem(40) {} 
};

class Apple : public GameItem {
public:
    Apple() : GameItem(1) {} 
};

#endif 
