#ifndef GAMEITEM_H
#define GAMEITEM_H
template <typename T>
class GameItem {
private:
    T data;  

public:

    GameItem(T d) : data(d) {}


    T getData() const { return data; }


    void setData(const T& d) { data = d; }
};
class SmallHealthPotion : public GameItem<int> {
public:
    SmallHealthPotion() : GameItem<int>(10) {}  
};


class HealthPotion : public GameItem<int> {
public:
    HealthPotion() : GameItem<int>(20) {}  
};


class BigHealthPotion : public GameItem<int> {
public:
    BigHealthPotion() : GameItem<int>(40) {}  
};


class Apple : public GameItem<int> {
public:
    Apple() : GameItem<int>(1) {}  
};

#endif