#include "topic4.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>
#include "../../basemap/GameEntities/gameItem.h"

Topic4::Topic4()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic4::Topic4(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{true, true, true}, {true, true, false}, {true, true, true}}} {
}

Topic4::~Topic4() {

}

void Topic4::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic4::uncompletedSquare() {
    if (!squares[baseMap->previousPlayerPosition.first][baseMap->previousPlayerPosition.second] && !squares[baseMap->playerPosition.first][baseMap->playerPosition.second]) {
        return true; 
    }
    return false;}

void Topic4::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
}

void Topic4::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    std::cout << "You found an Item!\n";
}

void Topic4::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);
std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic4::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayMapWithPlayer(squares, baseMap);
    
}

void Topic4::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic4::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayMapWithPlayer(squares, baseMap);
    displayWithDelay("You have met up against a CLAS TUTOR! the caveman", 1000); 
    displayWithDelay("CLAS TUTOR launches a weak attack: What does the default assignment operator perform in a class?", 1000); 

    printChoices("answers", "Deep copy", "Shallow copy","Deletes the object","None of the above");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "2","","",baseMap)) {
        displayWithDelay("CLAS TUTOR launches a critical attack! The special member function used to initialize an object when it is created is the ________.", 1000); 
        printChoices("answers", "Class", "Assignment operator","Destructor","Constructor");
        startInputListener();
        if(validateChoice(getCurrentInput(), "4","","",baseMap)) {
            squares[1][2] = true; 
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

void Topic4::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic4::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic4::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic4::handleCurrentSquare() {
    auto position = baseMap->getCurrentLocaiton();
    int x = position.first;
    int y = position.second;

    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        if (squares[x][y]) {
            displayMapWithPlayerI();
            std::cout << "[What is the past tense of square? Sqore? ... this is a calm square]\n";
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

