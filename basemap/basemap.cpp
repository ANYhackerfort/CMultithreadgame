#include "basemap.h"
#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <queue>

typedef std::pair<int, int> location; 
BaseMap::BaseMap() : playerPosition({1, 1}) {}

BaseMap::~BaseMap() {}

void BaseMap::displayWithDelay(const std::string& message, int delayMs) {
    std::cout << message << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
}

void BaseMap::moveNorth() {
    if (playerPosition.first > 0) {
        playerPosition.first--;
    } else {
        std::cout << "You hit an invisible wall to the north.\n";
    }
}

void BaseMap::moveSouth() {
    if (playerPosition.first < 2) {
        playerPosition.first++;
    } else {
        std::cout << "You hit an invisible wall to the south.\n";
    }
}

void BaseMap::moveWest() {
    if (playerPosition.second > 0) {
        playerPosition.second--;
    } else {
        std::cout << "You hit an invisible wall to the west.\n";
    }
}

void BaseMap::moveEast() {
    if (playerPosition.second < 2) {
        playerPosition.second++;
    } else {
        std::cout << "You hit an invisible wall to the east.\n";
    }
}

void BaseMap::startInputListener() {
    while (health > 0 && completedSquares < 10) {
        std::string userChoice;
        std::getline(std::cin, userChoice);
        if (userChoice == "1" || userChoice == "2" || userChoice == "3" || userChoice == "4") {
            input.push(userChoice); 

            if (input.size() > 1) {
                input.pop();
            }
            break;
        } if (userChoice == "exit") {
            std::cout << "Exiting the square... All your progress is lost!\n";
            input.push(""); 
            if (input.size() > 1) {
                input.pop();
            }
            break;
        } else {
            std::cout << "Invalid choice! Please enter a valid choice (1, 2, 3, 4, or exit to move to another square).\n";
            input.push(userChoice); 

            if (input.size() > 1) {
                input.pop();
            }
            break; 
        }
    }
}

std::string BaseMap::getCurrentInput() {
    while (input.empty()) {
    }

    std::string currentInput = input.front();
    return currentInput;
}


location BaseMap::getCurrentLocaiton() {
    return playerPosition; 
}

void BaseMap::printChoices(const std::string& chooseWhat, 
                           const std::string& choice1, 
                           const std::string& choice2, 
                           const std::string& choice3, 
                           const std::string& choice4) {
    std::cout << "Choose a " << chooseWhat << ":\n";
    std::cout << "1: " << choice1 << "\n";
    std::cout << "2: " << choice2 << "\n";
    std::cout << "3: " << choice3 << "\n";
    std::cout << "4: " << choice4 << "\n";
}

void BaseMap::validateChoice(const std::string& choice, const std::string& rightChoice, const std::string& winningMessage, const std::string& losingMessage) {
    if (choice == rightChoice) {
        std::cout << winningMessage << std::endl;
    } else if (choice == "") {
    } else {
        std::cout << losingMessage << " {-18 health!}";
        health -= 18;
    }
}