#include "topic8.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>

Topic8::Topic8()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic8::Topic8(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {
}

Topic8::~Topic8() {

}

void Topic8::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic8::uncompletedSquare() {
    return !squares[baseMap->playerPosition.first][baseMap->playerPosition.second];
}

void Topic8::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
        
    displayWithDelay("You have encountered abs! A boss of this level!", 1000); 
    displayWithDelay("abs launches a weak attack: A class containing at least one pure virtual function is called an abstract class.", 1500); 

    printChoices("answers", "True", "False");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "1","","",baseMap)) {
        displayWithDelay("abs launches an attack: Which of the following statements about an abstract class is true in C++?", 1500); 
        printChoices("answers", "An abstract class can be instantiated directly.","An abstract class cannot have member functions.","An abstract class must contain at least one pure virtual function.","An abstract class cannot be inherited.");
        startInputListener();
        if(validateChoice(getCurrentInput(), "3","","",baseMap)) {
            squares[0][0] = true; 
            baseGame->completedSquares++;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this boss (Marked in X)!, You are free to trasverse this level!");
        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic8::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic8::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic8::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic8::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    std::cout << "This is the starter square\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic8::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayWithDelay("You found a box of apples!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic8::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic8::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic8::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic8::handleCurrentSquare() {
    auto position = baseMap->getCurrentLocaiton();
    int x = position.first;
    int y = position.second;

    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        if (squares[x][y]) {
            std::cout << "You have already completed this level, you are free to move through it!\n";
            displayMapWithPlayerI();
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

