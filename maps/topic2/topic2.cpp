#include "topic2.h"
#include "../../basemap/maingame.h"
#include "../../basemap/basemap.h"
#include <iostream>
#include <memory>
#include "../../basemap/GameEntities/gameItem.h"

Topic2::Topic2()
    : baseMap(std::make_shared<BaseMap>()), // Create a new BaseMap using shared_ptr
      baseGame(std::make_shared<AdventureGame>()),
      squares{{{false, false, false}, {false, false, false}, {false, false, false}}} {}

Topic2::Topic2(std::shared_ptr<BaseMap>& existingBaseMap, std::shared_ptr<AdventureGame>& existingBaseGame)
    : baseMap(existingBaseMap),
      baseGame(existingBaseGame),
      squares{{{true, true, true}, {false, true, true}, {true, false, true}}} {
}

Topic2::~Topic2() {

}

void Topic2::displayMapWithPlayerI() { 
    displayMapWithPlayer(squares, baseMap);
}

bool Topic2::uncompletedSquare() {
    if (!squares[baseMap->previousPlayerPosition.first][baseMap->previousPlayerPosition.second] && !squares[baseMap->playerPosition.first][baseMap->playerPosition.second]) {
        return true; 
    }
    return false;
}

void Topic2::handleSquare00() {
    displayMapWithPlayer(squares, baseMap);
}

void Topic2::handleSquare01() {
    std::cout << "You are on the Mountain.\n";
    std::cout << "You found an Item!\n";
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
}

void Topic2::handleSquare02() {
    std::cout << "You are by the River.\n";
    displayMapWithPlayer(squares, baseMap);

}

void Topic2::handleSquare10() {
    std::cout << "You are in the Village.\n";
    displayMapWithPlayer(squares, baseMap);
    
    displayWithDelay("You have met up against [Custom Template Class]! the evil villager!", 1000); 
    displayWithDelay("[Custom Template Class] launches a weak attack: How do you define a template class with 2 parameters?", 1000); 

    printChoices("answers", "T<T>", "template <typename T1, typename T2>","template <type T1, type T2>","template <T1,T2>");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "2","","",baseGame)) {
        displayWithDelay("[Custom Template Class] launches a critical attack! True or False: Template classes in C++ improve runtime performance.", 1000); 
        printChoices("answers", "True", "False");
        startInputListener();
        if(validateChoice(getCurrentInput(), "2","","",baseGame)) {
            squares[1][0] = true; 
            baseGame->completedSquares++;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this level!, You are free to trasverse this level (Marked in X)!");
            displayWithDelay("You got an item!");
            std::string healthPotionKey = "HealthPotion";
            std::shared_ptr<HealthPotion> healthPotion = std::make_shared<HealthPotion>();
            baseGame->addItem(healthPotionKey, healthPotion);

        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic2::handleSquare11() {
    std::cout << "You are in the Castle.\n";
    displayWithDelay("You found an item!");
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
    displayMapWithPlayer(squares, baseMap);
}

void Topic2::handleSquare12() {
    std::cout << "You are in the Cave.\n";
    std::cout << "You found an Item!\n";
    std::shared_ptr<Apple> appleItem = std::make_shared<Apple>();
    std::string apple = "apple"; 
    baseGame->addItem(apple, appleItem);
    displayMapWithPlayer(squares, baseMap);
    
}

void Topic2::handleSquare20() {
    std::cout << "You are in the Field.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic2::handleSquare21() {
    std::cout << "You are by the Lake.\n";
    displayMapWithPlayer(squares, baseMap);
    displayWithDelay("You have met up against [Custom Template Class1]! the lake gnome!", 1000); 
    displayWithDelay("[Custom Template Class1] launches a weak attack: A template class can have both template and non-template member functions.", 1000); 

    printChoices("answers", "True", "False");
    startInputListener(); //auto stops each time, you have to type this each time
    if(validateChoice(getCurrentInput(), "1","","",baseGame)) {
        displayWithDelay("[Custom Template Class1] launches a critical attack! What symbol is used to specify a template parameter in C++?", 1000); 
        printChoices("answers", "<>", "T","()","[]");
        startInputListener();
        if(validateChoice(getCurrentInput(), "1","","",baseGame)) {
            squares[2][1] = true; 
            baseGame->completedSquares++;
            displayMapWithPlayer(squares, baseMap);
            displayWithDelay("You beat this level!, You are free to trasverse this level (Marked in X)!");
            displayWithDelay("You got an item!");
            std::string healthPotionKey = "HealthPotion";
            std::shared_ptr<HealthPotion> healthPotion = std::make_shared<HealthPotion>();
            baseGame->addItem(healthPotionKey, healthPotion);
        } else {
            displayWithDelay("You lost, progress reset!");
        }
    } else {
        displayWithDelay("You lost, progress reset!");
    }
}

void Topic2::handleSquare22() {
    std::cout << "You are in the Desert.\n";
    displayMapWithPlayer(squares, baseMap);
}

void Topic2::handleCurrentSquare() {
    auto position = baseMap->getCurrentLocaiton();
    int x = position.first;
    int y = position.second;

    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
        if (squares[x][y]) {
            displayMapWithPlayerI();
            std::cout << "[A calm square ...]\n";
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

