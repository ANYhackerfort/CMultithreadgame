#include "topic10.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>

Topic10::Topic10()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic10::Topic10(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{false, true, false}, {true, true, true}, {true, true, true}}} {
}

Topic10::~Topic10() {

}

void Topic10::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic10::uncompletedSquare() {
    if (!squares[baseMap->previousPlayerPosition.first][baseMap->previousPlayerPosition.second] && !squares[baseMap->playerPosition.first][baseMap->playerPosition.second]) {
        return true; 
    }
    return false;}

void Topic10::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
        
    displayWithDelay("You have encountered Sortie! A boss of this level!", 1000); 
    displayWithDelay("Sortie launches a weak attack: Which of the following sorting algorithms has the best average-case time complexity?", 1500); 

    printChoices("answers", "Bubble sort", "Insertion sort","Selection sort", "Quicksort");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "4","","",baseMap)) {

        // displayWithDelay("You have met up against [std::map] again! the final Ohio boss of this level!", 1000); 
        displayWithDelay("Sortie launches an attack: The worst-case time complexity of MergeSort is O(n log n).", 1500); 
        printChoices("answers", "True","False");
        startInputListener();
        if(validateChoice(getCurrentInput(), "1","","",baseMap)) {
            squares[0][0] = true; 
            baseGame->completedSquares++;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this boss!, You are free to trasverse this level!");
        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic10::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic10::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);

    displayWithDelay("You have encountered a bubble!", 1000); 
    displayWithDelay("Bubble launches a attack: The time complexity of Bubble Sort in the best case scenario (when the array is already sorted) is ________?", 1500); 

    printChoices("answers", "O(1)", "O(N^2)","O(N)","O(N^3)");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "3","","",baseMap)) {

        // displayWithDelay("You have met up against [std::map] again! the final Ohio boss of this level!", 1000); 
        displayWithDelay("bubble launches another attack: Insertion Sort has a time complexity of O(n^2) in the best case.", 1500); 
        printChoices("answers", "True","False");
        startInputListener();
        if(validateChoice(getCurrentInput(), "2","","",baseMap)) {
            squares[0][2] = true; 
            baseGame->completedSquares++;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this boss!, You are free to trasverse this level!");
        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic10::handleSquare10() {
    std::cout << "You are in the Village.\n";
    std::cout << "You found an item!\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic10::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    std::cout << "This is the starter square\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic10::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayWithDelay("There is nothing in the Cave.\n");
    displayMapWithPlayer(squares, baseMap);
}

void Topic10::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic10::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic10::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic10::handleCurrentSquare() {
    auto position = baseMap->getCurrentLocaiton();
    int x = position.first;
    int y = position.second;

    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        if (squares[x][y]) {
            std::cout << "[You have already completed this square, you are free to move through it!]\n";
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

