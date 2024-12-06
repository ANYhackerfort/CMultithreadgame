#ifndef TOPIC6_H
#define TOPIC6_H

#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <string>
#include <array>
#include <memory>
#include <iostream>

class Topic6 : public BaseMap{
private:
    std::array<std::array<bool, 3>, 3> squares; 
    std::shared_ptr<BaseMap> baseMap; 
    std::shared_ptr<AdventureGame> baseGame; 

public:
    Topic6();
    Topic6(std::shared_ptr<BaseMap>&  existingBaseMap, std::shared_ptr<AdventureGame>& existingAdventureGame);
    ~Topic6();

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

    void displayMapWithPlayerI();
    void handleCurrentSquare() override;
    bool uncompletedSquare() override;
};

#endif // TOPIC1_H
