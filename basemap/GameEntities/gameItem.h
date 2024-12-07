#ifndef GAME_ITEM_H
#define GAME_ITEM_H

class GameItem {
private:
    int data; // Integer data

public:
    // Constructor
    GameItem(int d) : data(d) {}

    // Getter
    int getData() const { return data; }

    // Setter
    void setData(int d) { data = d; }
};

// Specialized Game Items
class SmallHealthPotion : public GameItem {
public:
    SmallHealthPotion() : GameItem(10) {} // Restores 10 health points
};

class HealthPotion : public GameItem {
public:
    HealthPotion() : GameItem(20) {} // Restores 20 health points
};

class BigHealthPotion : public GameItem {
public:
    BigHealthPotion() : GameItem(40) {} // Restores 40 health points
};

class Apple : public GameItem {
public:
    Apple() : GameItem(1) {} // Restores 1 health point
};

#endif // GAME_ITEM_H
