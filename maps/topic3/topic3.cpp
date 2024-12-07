#include "topic3.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>
#include "../../basemap/GameEntities/gameItem.h"

Topic3::Topic3()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic3::Topic3(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {
}

Topic3::~Topic3() {

}

void Topic3::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic3::uncompletedSquare() {
    return !squares[baseMap->playerPosition.first][baseMap->playerPosition.second];
}

void Topic3::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
}

void Topic3::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    std::cout << "You found an Item!\n";
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic3::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic3::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayMapWithPlayer(squares, baseMap);
    
}

void Topic3::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic3::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayMapWithPlayer(squares, baseMap);
    displayWithDelay("You have met up against [Custom Namespace]! the cave bata!", 1000); 
    displayWithDelay("[Custom Namespace] launches a weak attack: How do you define a namespace in C++?", 1000); 

    printChoices("answers", "namespace Name { ... }", "using Name { ... }","define Name { ... }","namespace { ... }");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "1","","",baseMap)) {
        displayWithDelay("[Custom Namespace] launches a critical attack! namespace myNamespace = longNamespaceName;", 1000); 
        printChoices("answers", "This is not allowed in C++", "This will create a copy of the namespace.","This creates an alias myNamespace for longNamespaceName.","This will result in an error.");
        startInputListener();
        if(validateChoice(getCurrentInput(), "3","","",baseMap)) {
            squares[1][2] = true; 
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

void Topic3::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic3::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic3::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic3::handleCurrentSquare() {
    auto position = baseMap->getCurrentLocaiton();
    int x = position.first;
    int y = position.second;

    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        if (squares[x][y]) {
            displayMapWithPlayerI();
            std::cout << "You have already completed this level, you are free to move through it!\n";
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

