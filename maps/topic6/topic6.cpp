#include "topic6.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>

Topic6::Topic6()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic6::Topic6(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {
}

Topic6::~Topic6() {

}

void Topic6::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic6::uncompletedSquare() {
    return !squares[baseMap->playerPosition.first][baseMap->playerPosition.second];
}

void Topic6::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
}

void Topic6::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayMapWithPlayer(squares, baseMap);
    
    displayWithDelay("You have encountered [basics of exception handling]! the a boss of this level!", 1000); 
    displayWithDelay("[std::map] launches a weak attack: What is the purpose of exception handling in C++?", 1500); 

    printChoices("answers", "To terminate a program immediately when an error occurs", "To handle runtime errors in a structured and recoverable way","To debug compile-time errors","To improve code readability");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "2","","",baseMap)) {

        // displayWithDelay("You have met up against [std::map] again! the final Ohio boss of this level!", 1000); 
        displayWithDelay("[basics of exception handling] launches an attack: Which of the following is the correct syntax to throw an exception in C++?", 1500); 
        printChoices("answers", "throw exception_type;", "throw new exception_type();","throw exception_type();","throw;");
        startInputListener();
        if(validateChoice(getCurrentInput(), "4","","",baseMap)) {
            squares[0][1] = true; 
            ++completedSquares;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this level!, You are free to trasverse this level (Marked in X)!");
        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic6::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic6::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic6::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic6::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic6::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic6::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic6::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic6::handleCurrentSquare() {
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

