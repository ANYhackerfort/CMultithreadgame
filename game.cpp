#include <iostream>
#include "./basemap/maingame.h"
#include "./maps/topic1/topic1.h"
#include "./basemap/basemap.h"
#include <thread>
#include <memory>
#include <atomic>
#include <chrono>

std::atomic<bool> isGameRunning(true);

void displayLoadingScreen() {
    std::cout << "\nDid you know you can type:\n";
    std::cout << "  - /lookuphealth to check your health stats\n";
    std::cout << "  - /displayinventory to see your inventory\n";
    std::cout << "  - /displaymap to view the map\n";
    std::string loadingAnimation[] = {
        "[*        ] Loading map...",
        "[**       ] Loading map...",
        "[***      ] Loading map...",
        "[****     ] Loading map...",
        "[*****    ] Loading map...",
        "[******   ] Loading map...",
        "[*******  ] Loading map...",
        "[******** ] Loading map...",
        "[*********] Loading complete!"
    };

    for (const auto& frame : loadingAnimation) {
        std::cout << "\r" << frame << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    }
    std::cout << std::endl;
}

BaseMap* processUserChoice(std::shared_ptr<BaseMap>& map, std::string& mapNumber) {
    if (mapNumber == "1") {
        std::cout << "Arrived at Standard Library Containers (map, vector, etc.)\n";
        return new Topic1(map); 
    } else if (mapNumber == "2") {
        std::cout << "Arrived at Custom Template Class\n";
    } else if (mapNumber == "3") {
        std::cout << "Arrived at Custom Namespace\n";
    } else if (mapNumber == "4") {
        std::cout << "Arrived at Classes with Constructor, Destructor, Assignment Operator\n";
    } else if (mapNumber == "5") {
        std::cout << "Arrived at Lambda Functions\n";
    } else if (mapNumber == "6") {
        std::cout << "Arrived at Exception Handling\n";
    } else if (mapNumber == "7") {
        std::cout << "Arrived at Inheritance\n";
    } else if (mapNumber == "8") {
        std::cout << "Arrived at Virtual Functions or Abstract Classes\n";
    } else if (mapNumber == "9") {
        std::cout << "Arrived at Hashing\n";
    } else if (mapNumber == "10") {
        std::cout << "Arrived at Sorting Algorithms\n";
    } else {
        return nullptr;
    }
    return nullptr;
}

void handleMapSelection(AdventureGame& game, std::shared_ptr<BaseMap>& map, std::string& mapNumber) {
    std::string userChoice;
    while (true) {
        std::cout << "\nEnter the number of the map you'd like to transport to: ";
        std::cin >> userChoice;

        if (game.hasTopicsByID(userChoice)) {
            std::cout << "Transporting to... ";
            game.displayTopicsByID(userChoice);
            displayLoadingScreen();
            mapNumber = userChoice;
            break;
        } else {
            std::cout << "Invalid map number. Please try again.\n";
        }
    }
}

void commandListener(AdventureGame& game, std::shared_ptr<BaseMap>& map, std::string& mapNumber) {
    std::string input;

    while (isGameRunning) {
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "movenorth" || input == "movewest" || input == "movesouth" || input == "moveeast") {
            BaseMap* currentMap = processUserChoice(map, mapNumber);
            // std::cout << map.use_count();
            if (input == "movenorth") {
                std::cout << "<<Moved North>>" << std::endl;
                map->moveNorth();
            } else if (input == "movesouth") {
                std::cout << "<<moved South>>" << std::endl;
                map->moveSouth();
            } else if (input == "movewest") {
                std::cout << "<<moved West>>" << std::endl;
                map->moveWest();
            } else if (input == "moveeast") {
                std::cout << "<<moved East>>" << std::endl;
                map->moveEast();
            }
            if (currentMap) {
                currentMap->handleCurrentSquare();
            } else {
                std::cout << "No valid map to handle." << std::endl;
            }
            delete currentMap;
        }

        if (!input.empty() && input[0] == '/') {
            if (input == "/lookuphealth") {
                game.displayStats();
            } else if (input == "/displayinventory") {
                game.displayInventory();
            } else if (input == "/displaymap") {
                game.displayTopics();
                handleMapSelection(game, map, mapNumber);
            } else {
                std::cout << "Unknown command: " << input << std::endl;
            }
        }
    }
}

void checkStatus(AdventureGame& game) {
    while (isGameRunning) {
        if (game.returnHealth() <= 0) {
            std::cout << "You have DIED! All Progress Lost!" << std::endl;
            isGameRunning = false; 
        } else if (game.completedSquares > 10) {
            std::cout << "You have WON! Thanks for playing!" << std::endl;
            isGameRunning = false; 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main() {
    AdventureGame game;
    std::shared_ptr<BaseMap> map = std::make_shared<BaseMap>();
    // std::shared_ptr<BaseMap> anotherMap = map;
    std::string mapNumber;

    std::cout << "Welcome to Nabeel's open world; Elden Ring Style Game! Full freedom to explore!\n";
    std::thread inputThread1(commandListener, std::ref(game), std::ref(map), std::ref(mapNumber));
    std::thread inputThread2(checkStatus, std::ref(game));

    std::cout << "\nDid you know you can type:\n";
    std::cout << "  - /stats to check completed squares and your other stats\n";
    std::cout << "  - /displayinventory to see your inventory\n";
    std::cout << "  - /displaymap to view the map\n";

    inputThread1.join();
    inputThread1.join();

    return 0;
}
