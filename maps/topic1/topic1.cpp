#include "topic1.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>

Topic1::Topic1()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic1::Topic1(std::shared_ptr<BaseMap>& existingBaseMap)
    : baseMap(existingBaseMap),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {
}

Topic1::~Topic1() {

}

void Topic1::handleSquare00() {

}

void Topic1::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    
    displayWithDelay("You have met up against [std::map]! the final Ohio boss of this level!", 1000); 
    displayWithDelay("[std::map] launches a weak attack: how to traverse a map BACKWARDS!", 1500); 

    printChoices("answers", "for (auto rit = myMap.rbegin(); rit != myMap.rend(); ++rit)", "for (auto rit = myMap.rbegin(); rit != myMap.rend(); --rit)");
    startInputListener(); //auto stops each time, you have to type this each time
    validateChoice(getCurrentInput(), "1");

    squares[0][0] = true; 
    ++completedSquares;
}

void Topic1::handleSquare02() {
    std::cout << "You are by the River.\n";
}

void Topic1::handleSquare10() {
    std::cout << "You are in the Village.\n";
}

void Topic1::handleSquare11() {
    std::cout << "You are in the Castle.\n";
}

void Topic1::handleSquare12() {
    std::cout << "You are in the Cave.\n";
}

void Topic1::handleSquare20() {
    std::cout << "You are in the Field.\n";
}

void Topic1::handleSquare21() {
    std::cout << "You are by the Lake.\n";
}

void Topic1::handleSquare22() {
    std::cout << "You are in the Desert.\n";
}

void Topic1::handleCurrentSquare() {
    auto position = baseMap->getCurrentLocaiton();
    int x = position.first;
    int y = position.second;

    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        if (squares[x][y]) {
            std::cout << "You have already completed this level, you can no longer access it.\n";
        } else {
            if (x == 0 && y == 0) handleSquare00();
            else if (x == 0 && y == 1) handleSquare01();
            else if (x == 0 && y == 2) handleSquare02();
            else if (x == 1 && y == 0) handleSquare10();
            else if (x == 1 && y == 1) handleSquare11();
            else if (x == 1 && y == 2) handleSquare12();
            else if (x == 2 && y == 0) handleSquare20();
            else if (x == 2 && y == 1) handleSquare21();
            else if (x == 2 && y == 2) handleSquare22();

            squares[x][y] = false;
        }
    } else {
        std::cout << "Invalid position.\n";
    }
}

