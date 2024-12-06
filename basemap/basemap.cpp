#include "basemap.h"
#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <queue>
#include<memory>
typedef std::pair<int, int> location; 
BaseMap::BaseMap() : playerPosition({1, 1}) {}

BaseMap::~BaseMap() {}

void BaseMap::displayMapWithPlayer(const std::array<std::array<bool, 3>, 3>& squares, const std::shared_ptr<BaseMap> baseMap) {
    std::cout << "Map Squares:\n";
    for (int row = 0; row < squares.size(); ++row) {
        for (int col = 0; col < squares[row].size(); ++col) {
            if (baseMap->playerPosition.first == row && baseMap->playerPosition.second == col) {
                std::cout << (squares[row][col] ? "[XO]" : "[O]") << " ";
            } else {
                std::cout << (squares[row][col] ? "[X]" : "[ ]") << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void BaseMap::displayWithDelay(const std::string& message, int delayMs) {
    std::cout << message << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
}

void BaseMap::moveNorth() {
    if (playerPosition.first > 0) {
        playerPosition.first--;
        std::cout << "<<Moved North>>" << std::endl;
    } else {
        std::cout << "You hit an invisible wall to the north.\n";
    }
}

void BaseMap::moveSouth() {
    if (playerPosition.first < 2) {
        playerPosition.first++;
        std::cout << "<<Moved South>>" << std::endl;
    } else {
        std::cout << "You hit an invisible wall to the south.\n";
    }
}

void BaseMap::moveWest() {
    if (playerPosition.second > 0) {
        playerPosition.second--;
        std::cout << "<<Moved West>>" << std::endl;
    } else {
        std::cout << "You hit an invisible wall to the west.\n";
    }
}

void BaseMap::moveEast() {
    if (playerPosition.second < 2) {
        playerPosition.second++;
        std::cout << "<<Moved East>>" << std::endl;
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

bool BaseMap::validateChoice(const std::string& choice, 
                             const std::string& rightChoice, 
                             const std::string& winningMessage, 
                             const std::string& losingMessage, 
                             const std::shared_ptr<BaseMap>& existingBaseMap) {
    if (choice == rightChoice) {
        std::cout << winningMessage << std::endl;
        return true; 
    } else if (choice == "") {
        return false; 
    } else {
        std::cout << losingMessage << " {-18 health!}" << std::endl;
        if (existingBaseMap) {
            existingBaseMap->health -= 18; // Adjust health only if existingBaseMap is valid
        }
        return false; 
    }
}
