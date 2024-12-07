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
#endif