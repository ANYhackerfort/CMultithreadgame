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
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {
}

Topic1::~Topic1() {

}

void Topic1::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic1::uncompletedSquare() {
    return !squares[baseMap->playerPosition.first][baseMap->playerPosition.second];
}

void Topic1::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
}

void Topic1::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayMapWithPlayer(squares, baseMap);
    
    displayWithDelay("You have met up against [std::map]! the final Ohio gnome boss of this level!", 1000); 
    displayWithDelay("[std::map] launches a weak attack: how to traverse a map BACKWARDS!", 1500); 

    printChoices("answers", "for (auto rit = myMap.rbegin(); rit != myMap.rend(); ++rit)", "for (auto rit = myMap.rbegin(); rit != myMap.rend(); --rit)");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "1","","",baseGame)) {
        // displayWithDelay("You beat the square!");

        displayWithDelay("You have met up against [std::map] again! the final Ohio boss of this level!", 1000); 
        displayWithDelay("[std::map] launches a weak attack: how to traverse a map BACKWARDS!", 1500); 
        printChoices("answers", "for (auto rit = myMap.sdfsdfsdf(); rit != myMap.rend(); ++rit)", "for (auto rit = myMap.rbegin(); rit != myMap.rend(); --rit)");
        startInputListener();
        if(validateChoice(getCurrentInput(), "1","","",baseGame)) {
            squares[0][1] = true; 
            baseGame->completedSquares++;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this level!, You are free to trasverse this level (Marked in X)!");
            displayWithDelay("You got an item!");
            Apple Apple; 
            std::string apple = "apple"; 
            baseGame->addItem(apple, Apple);
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

