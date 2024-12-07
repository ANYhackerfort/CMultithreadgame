#include "topic7.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>

Topic7::Topic7()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic7::Topic7(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {
}

Topic7::~Topic7() {

}

void Topic7::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic7::uncompletedSquare() {
    return !squares[baseMap->playerPosition.first][baseMap->playerPosition.second];
}

void Topic7::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
        
    displayWithDelay("You have encountered grampa! A boss of this level!", 1000); 
    displayWithDelay("grampa launches a weak attack: Inheritance allows a class to acquire properties and methods from another class.", 1500); 

    printChoices("answers", "True", "False");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "1","","",baseMap)) {

        // displayWithDelay("You have met up against [std::map] again! the final Ohio boss of this level!", 1000); 
        displayWithDelay("gramps launches an attack: What is the name of the class being inherited from?", 1500); 
        printChoices("answers", "Base class","Derived class","SigmaClass","All of the above");
        startInputListener();
        if(validateChoice(getCurrentInput(), "1","","",baseMap)) {
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

void Topic7::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic7::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);

    displayWithDelay("You have encountered a dad!", 1000); 
    displayWithDelay("dad launches a attack: What happens if no access specifier is provided in inheritance?", 1500); 

    printChoices("answers", "Public inheritance by default", "Private inheritance by default","Protected inheritance by default","No inheritance occurs");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "2","","",baseMap)) {

        // displayWithDelay("You have met up against [std::map] again! the final Ohio boss of this level!", 1000); 
        displayWithDelay("dad launches another attack: What is the order of constructor calls in inheritance?", 1500); 
        printChoices("answers", "Derived class constructor, then base class constructor","Base class constructor, then derived class constructor","Constructors are called simultaneously","None of the above");
        startInputListener();
        if(validateChoice(getCurrentInput(), "2","","",baseMap)) {
            squares[0][2] = true; 
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

void Topic7::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayWithDelay("You found an item!");
    Apple Apple; 
    std::string apple = "apple"; 
    baseGame->addItem(apple, Apple);
    displayMapWithPlayer(squares, baseMap);

}

void Topic7::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    std::cout << "This is the starter square\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic7::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayWithDelay("There is nothing in the Cave.\n");
    displayMapWithPlayer(squares, baseMap);
}

void Topic7::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayWithDelay("You found an item!");
    Apple Apple; 
    std::string apple = "apple"; 
    baseGame->addItem(apple, Apple);
    displayMapWithPlayer(squares, baseMap);
}

void Topic7::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic7::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic7::handleCurrentSquare() {
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

