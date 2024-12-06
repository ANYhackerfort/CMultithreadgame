#ifndef TOPIC1_H
#define TOPIC1_H

#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <string>
#include <array>
#include <memory>
#include <iostream>

class Topic1 : public BaseMap{
private:
    std::array<std::array<bool, 3>, 3> squares; 
    std::shared_ptr<BaseMap> baseMap; 

public:
    Topic1();
    Topic1(std::shared_ptr<BaseMap>&  existingBaseMap);
    ~Topic1();

    //story implementation bla bla bla
    void handleSquare00();
    void handleSquare01();
    void handleSquare02();
    void handleSquare10();
    void handleSquare11();
    void handleSquare12();
    void handleSquare20();
    void handleSquare21();
    void handleSquare22();

    void handleCurrentSquare() override;
};

#endif // TOPIC1_H
