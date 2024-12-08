#include "topic1.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>
#include "../../basemap/GameEntities/gameItem.h"

Topic1::Topic1()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic1::Topic1(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{true, false, true}, {true, true, true}, {true, true, true}}} {}

Topic1::~Topic1() {

}

void Topic1::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic1::uncompletedSquare() {
    std::cout << "HELLO";
    return !squares[baseMap->previousPlayerPosition.first][baseMap->previousPlayerPosition.second];
}

void Topic1::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
}

void Topic1::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayMapWithPlayer(squares, baseMap);
    
    displayWithDelay("You have met up against [std::map]! a sigma Ohio gnome boss of this level!", 1000); 
    displayWithDelay("[std::map] launches a weak attack: how to traverse a map BACKWARDS!", 1500); 

    printChoices("answers", "for (auto rit = myMap.rbegin(); rit != myMap.rend(); ++rit)", "for (auto rit = myMap.rbegin(); rit != myMap.rend(); --rit)","for (auto it = myMap.begin(); rit != myMap.end(); --it)","for (auto it = myMap.begin(); rit != myMap.end(); ++it)");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "1","","",baseGame)) {
        // displayWithDelay("You beat the square!");

        displayWithDelay("You have met up against [std::vector]! the final Ohio boss of this level!", 1000); 
        displayWithDelay("[std::vector] launches a weak attack: Which of the following statements is true about std::vector in C++?", 1500); 
        printChoices("answers", "std::vector has a fixed size that cannot be changed after initialization.", "Elements in a std::vector are stored contiguously in memory.","Accessing elements in a std::vector can only be done using iterators.","std::vector automatically manages memory and cannot cause memory leaks.");
        startInputListener();
        if(validateChoice(getCurrentInput(), "2","","",baseGame)) {
            squares[0][1] = true; 
            baseGame->completedSquares++;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this level!, You are free to trasverse this level (Marked in X)!");
            displayWithDelay("You got an item!");
            std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
            std::string apple = "apple"; 
            baseGame->addItem(apple, appleItem);
        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic1::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic1::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic1::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic1::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    std::cout << "You found an Item!\n";
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
    displayMapWithPlayer(squares, baseMap);
}

void Topic1::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic1::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic1::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic1::handleCurrentSquare() {
    auto position = baseMap->getCurrentLocaiton();
    int x = position.first;
    int y = position.second;

    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        if (squares[x][y]) {
            displayMapWithPlayerI();
            std::cout << "[A calm clam square...]!\n";
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
        }
    } else {
        std::cout << "Invalid position.\n";
    }
}

