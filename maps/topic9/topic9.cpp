#include "topic9.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>

Topic9::Topic9()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic9::Topic9(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {
}

Topic9::~Topic9() {

}

void Topic9::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic9::uncompletedSquare() {
    if (!squares[baseMap->previousPlayerPosition.first][baseMap->previousPlayerPosition.second] && !squares[baseMap->playerPosition.first][baseMap->playerPosition.second]) {
        return true; 
    }
    return false;}

void Topic9::handleSquare00() {
    std::cout << "You are in the Void.\nThere is nothing here...\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic9::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic9::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);

    displayWithDelay("You have encountered a hash brown!", 1000); 
    displayWithDelay("Hash brown launches a attack: Which of the following is a common technique used to handle hash collisions in a hash table?", 1500); 

    printChoices("answers", "binary search","Double hashing", "Quicksort", "Graph Traversal");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "2","","",baseMap)) {

        // displayWithDelay("You have met up against [std::map] again! the final Ohio boss of this level!", 1000); 
        displayWithDelay("Hash brown launches another attack: In hashing, a hash collision occurs when two different keys hash to the same index in a hash table.", 1500); 
        printChoices("answers", "True","False");
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

void Topic9::handleSquare10() {
    std::cout << "You are in the Village.\n";
    std::cout << "You found an item!\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic9::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    std::cout << "This is the starter square\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic9::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayWithDelay("There is nothing in the Cave.\n");
    displayMapWithPlayer(squares, baseMap);
}

void Topic9::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic9::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic9::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic9::handleCurrentSquare() {
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

