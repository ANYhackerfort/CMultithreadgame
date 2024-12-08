#include "topic5.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>
#include "../../basemap/GameEntities/gameItem.h"

Topic5::Topic5()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic5::Topic5(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{true, true, true}, {false, false, false}, {false, false, false}}} {
}

Topic5::~Topic5() {

}

void Topic5::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic5::uncompletedSquare() {
    return !squares[baseMap->playerPosition.first][baseMap->playerPosition.second];
}

void Topic5::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
}

void Topic5::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    displayWithDelay("You found a ton of apples!!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::shared_ptr<Apple> appleItem1 = std::make_shared<Apple>();
    std::shared_ptr<Apple> appleItem2 = std::make_shared<Apple>();
    std::shared_ptr<Apple> appleItem3 = std::make_shared<Apple>();
    std::shared_ptr<Apple> appleItem4 = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
    baseGame->addItem(apple, appleItem1);
    baseGame->addItem(apple, appleItem2);
    baseGame->addItem(apple, appleItem3);
    baseGame->addItem(apple, appleItem4);
}

void Topic5::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic5::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic5::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic5::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic5::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic5::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic5::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
    displayWithDelay("You have met up against a desert snake LAMBDA!", 1000); 
    displayWithDelay("Lambda launches a weak attack: A lambda function in C++ begins with the symbol ________?", 1000); 

    printChoices("answers", "[]", "()","Lambda","None of the above");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "1","","",baseMap)) {
        displayWithDelay("lambda launches a critical attack! Which of the following is a valid use of a lambda function?", 1000); 
        printChoices("answers", "Sorting a std::vector with std::sort", "Defining a quick callback function","Creating a custom predicate for std::find_if","All of the above");
        startInputListener();
        if(validateChoice(getCurrentInput(), "4","","",baseMap)) {
            displayWithDelay("lambda launches a critical attack! Lambdas with no capture list (e.g., []) can be converted to a function pointer.", 1000); 
            printChoices("answers", "True", "False");
            startInputListener();
            if(validateChoice(getCurrentInput(), "1","","",baseMap)) {
                squares[2][2] = true; 
                baseGame->completedSquares++;
                displayMapWithPlayer(squares, baseMap);
                displayWithDelay("You beat this level!, You are free to trasverse this level (Marked in X)!");
            }else{
                displayWithDelay("You lost, progress reset!");
            }
        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic5::handleCurrentSquare() {
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

