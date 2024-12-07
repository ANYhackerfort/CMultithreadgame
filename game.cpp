#include <iostream>
#include "./basemap/maingame.h"
#include "./maps/topic1/topic1.h"
#include "./maps/topic6/topic6.h"
#include "./basemap/basemap.h"
#include <thread>
#include <memory>
#include <atomic>
#include <chrono>
#include <algorithm>

std::atomic<bool> isGameRunning(true);

//store all maps, dont forget to clean
Topic1* topic1Map; 
Topic6* topic6Map; 

void loadMaps(std::shared_ptr<BaseMap>& map, std::shared_ptr<AdventureGame>& game) {
    if (topic1Map == nullptr) { 
        topic1Map = new Topic1(map, game);
        topic6Map = new Topic6(map, game);
    }
}

void deleteMaps() {
    delete topic1Map;
    delete topic6Map;
}



BaseMap* processUserChoice(std::shared_ptr<BaseMap>& map, std::shared_ptr<AdventureGame>&game, std::string& mapNumber) {
    
    if (mapNumber == "1") {
        std::cout << "Arrived at Standard Library Containers (map, vector, etc.)\n";
        return topic1Map; 
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
        return topic6Map;
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
}

void handleMapSelection(std::shared_ptr<AdventureGame>&game, std::shared_ptr<BaseMap>& map, std::string& mapNumber) {
     auto displayAnimation = []() {
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
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << std::endl;
    };

    std::string userChoice;
    while (true) {
        std::cout << "\nEnter the number of the map you'd like to transport to: ";
        std::cin >> userChoice;
        try{

            if (game->hasTopicsByID(userChoice)) {
                std::cout << "Transporting to... ";
                game->displayTopicsByID(userChoice);
                displayAnimation();
                if(userChoice=="1"){//make these for all topics
                    std::cout<< "Arrived at Standard Library Containers (map, vector, etc.)\n\n";
                    topic1Map->displayMapWithPlayerI();
                }else if(userChoice=="2"){
                    std::cout << "Arrived at Custom Template Class\n";
                }else if(userChoice=="3"){
                    
                }else if(userChoice=="4"){

                }else if(userChoice=="5"){
                    
                }else if(userChoice=="6"){
                    std::cout<<"Arrived at Exception Handling\n";
                    topic6Map->displayMapWithPlayerI();
                }else if(userChoice=="7"){
                    
                }else if(userChoice=="8"){
                    
                }else if(userChoice=="9"){
                    
                }else if(userChoice=="10"){
                    
                }
                mapNumber = userChoice;
                break;
            } else {
                throw std::invalid_argument("Invalid map number");
            }
        } catch(const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            // Handle the invalid map number scenario by returning nullptr
        }
    }
}

void commandListener(std::shared_ptr<AdventureGame>&game, std::shared_ptr<BaseMap>& map, std::string& mapNumber) {
    std::string input;

    while (isGameRunning) {
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "movenorth" || input == "movewest" || input == "movesouth" || input == "moveeast") {
            BaseMap* currentMap = processUserChoice(map, game, mapNumber);
            // std::cout << map.use_count();
            if (input == "movenorth") {
                map->moveNorth();
                if (map->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveSouth(); 
                }
            } else if (input == "movesouth") {
                map->moveSouth();
                if (map->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveNorth(); 
                }                
            } else if (input == "movewest") {
                map->moveWest();
                if (map->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveEast(); 
                }
            } else if (input == "moveeast") {
                map->moveEast();
                if (map->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveWest(); 
                }
            }
            if (currentMap) {
                currentMap->handleCurrentSquare();
            } else {
                std::cout << "No valid map to handle." << std::endl;
            }
        } else if (input == "stay") {
            BaseMap* currentMap = processUserChoice(map, game, mapNumber);
            if (currentMap) {
                currentMap->handleCurrentSquare();
            } else {
                std::cout << "No valid map to handle." << std::endl;
            }
        }
        try{
            if (!input.empty() && input[0] == '/') {
                if (input == "/stats"|| input == "/s"||input == "/health"||input == "/h") {
                    game->displayStats();
                } else if (input == "/displayinventory"|| input =="/i"|| input =="/inventory") {
                    game->displayInventory();
                } else if ((input == "/map")|| (input == "/m")||(input == "/map")) {
                    game->displayTopics();
                    handleMapSelection(game, map, mapNumber);
                } else {
                    throw std::invalid_argument("Invalid command: " + input);
                }
            }
        } catch(const std::invalid_argument& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void checkStatus(std::shared_ptr<AdventureGame>& game) {
    while (isGameRunning) {
        if (game->returnHealth() <= 0) {
            std::cout << "You have DIED! All Progress Lost!" << std::endl;
            isGameRunning = false; 
        } else if (game->completedSquares > 10) {
            std::cout << "You have WON! Thanks for playing!" << std::endl;
            isGameRunning = false; 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main() {
    std::shared_ptr<BaseMap> map = std::make_shared<BaseMap>();
    std::shared_ptr<AdventureGame> game = std::make_shared<AdventureGame>();
    loadMaps(map, game);

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

    deleteMaps(); //clear maps

    return 0;
}
