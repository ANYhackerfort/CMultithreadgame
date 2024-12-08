#include <iostream>
#include "./basemap/maingame.h"
#include "./maps/topic1/topic1.h"
#include "./maps/topic2/topic2.h"
#include "./maps/topic3/topic3.h"
#include "./maps/topic4/topic4.h"
#include "./maps/topic5/topic5.h"
#include "./maps/topic6/topic6.h"
#include "./maps/topic7/topic7.h"
#include "./maps/topic8/topic8.h"
#include "./maps/topic9/topic9.h"
#include "./maps/topic10/topic10.h"
#include "./basemap/basemap.h"
#include <thread>
#include <memory>
#include <atomic>
#include <chrono>
#include <algorithm>
#include <sstream>

std::atomic<bool> isGameRunning(true);

//store all maps, dont forget to clean
Topic1*  topic1Map; 
Topic2*  topic2Map;
Topic3*  topic3Map;
Topic4*  topic4Map;
Topic5*  topic5Map;
Topic6*  topic6Map; 
Topic7*  topic7Map; 
Topic8*  topic8Map;
Topic9*  topic9Map;
Topic10* topic10Map;

void loadMaps(std::shared_ptr<BaseMap>& map, std::shared_ptr<AdventureGame>& game) {
    if (topic1Map == nullptr) { 
        topic1Map = new Topic1(map, game);
        topic2Map = new Topic2(map, game);
        topic3Map = new Topic3(map, game);
        topic4Map = new Topic4(map, game);
        topic5Map = new Topic5(map, game);
        topic6Map = new Topic6(map, game);
        topic7Map = new Topic7(map, game);
        topic8Map = new Topic8(map, game);
        topic9Map = new Topic9(map, game);
        topic10Map = new Topic10(map, game);
    }
}

void deleteMaps() {
    delete topic1Map;
    delete topic2Map;
    delete topic3Map;
    delete topic4Map;
    delete topic5Map;
    delete topic6Map;
    delete topic7Map;
    delete topic8Map;
    delete topic9Map;
    delete topic10Map;
}

BaseMap* processUserChoice(std::shared_ptr<BaseMap>& map, std::shared_ptr<AdventureGame>&game, std::string& mapNumber) {
    std::cout << "Move around by typing: movenorth, movesouth, moveeast, movewest [not case-sensitive]" << std::endl;
    if (mapNumber == "1") {
        std::cout << "Arrived at Standard Library Containers (map, vector, etc.)\n";
        return topic1Map; 
    } else if (mapNumber == "2") {
        std::cout << "Arrived at Custom Template Class\n";
        return topic2Map;
    } else if (mapNumber == "3") {
        std::cout << "Arrived at Custom Namespace\n";
        return topic3Map;
    } else if (mapNumber == "4") {
        std::cout << "Arrived at Classes with Constructor, Destructor, Assignment Operator\n";
        return topic4Map;
    } else if (mapNumber == "5") {
        std::cout << "Arrived at Lambda Functions\n";
        return topic5Map;
    } else if (mapNumber == "6") {
        std::cout << "Arrived at Exception Handling\n";
        return topic6Map;
    } else if (mapNumber == "7") {
        std::cout << "Arrived at Inheritance\n";
        return topic7Map;
    } else if (mapNumber == "8") {
        std::cout << "Arrived at Virtual Functions or Abstract Classes\n";
        return topic8Map;
    } else if (mapNumber == "9") {
        std::cout << "Arrived at Hashing\n";
        return topic9Map;
    } else if (mapNumber == "10") {
        std::cout << "Arrived at Sorting Algorithms\n";
        return topic10Map;
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
                    topic2Map->displayMapWithPlayerI();
                    std::cout << "Arrived at Custom Template Class\n";
                }else if(userChoice=="3"){
                    topic3Map->displayMapWithPlayerI();
                    std::cout << "Arrived at Custom Namespace\n";
                }else if(userChoice=="4"){
                    std::cout << "Arrived at Classes with Constructor, Destructor, Assignment Operator\n";
                    topic4Map->displayMapWithPlayerI();
                }else if(userChoice=="5"){
                    std::cout << "Arrived at Lambda Functions\n";
                    topic5Map->displayMapWithPlayerI();
                }else if(userChoice=="6"){
                    std::cout<<"Arrived at Exception Handling\n";
                    topic6Map->displayMapWithPlayerI();
                }else if(userChoice=="7"){
                    std::cout << "Arrived at Inheritance\n";
                    topic7Map->displayMapWithPlayerI();
                }else if(userChoice=="8"){
                    std::cout << "Arrived at Virtual Functions or Abstract Classes\n";
                    topic8Map->displayMapWithPlayerI();
                }else if(userChoice=="9"){
                    std::cout << "Arrived at Hashing\n";
                    topic9Map->displayMapWithPlayerI();
                }else if(userChoice=="10"){
                    std::cout << "Arrived at Sorting Algorithms\n";
                    topic10Map->displayMapWithPlayerI();
                }
                mapNumber = userChoice;
                break;
            } else {
                throw std::invalid_argument("Invalid map number");
            }
        } catch(const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

void commandListener(std::shared_ptr<AdventureGame>& game, std::shared_ptr<BaseMap>& map, std::string& mapNumber) {
    std::string input;
    while (isGameRunning) {
        std::getline(std::cin, input);
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        std::istringstream iss(input);
        std::string command, subCommand, item;
        iss >> command >> subCommand >> item;

        if (command == "movenorth" || command == "movewest" || command == "movesouth" || command == "moveeast") {
            BaseMap* currentMap = processUserChoice(map, game, mapNumber);
            if (command == "movenorth") {
                map->moveNorth();
                if (currentMap->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveSouth();
                }
            } else if (command == "movesouth") {
                map->moveSouth();
                if (currentMap->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveNorth();
                }
            } else if (command == "movewest") {
                map->moveWest();
                if (currentMap->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveEast();
                }
            } else if (command == "moveeast") {
                map->moveEast();
                if (currentMap->uncompletedSquare()) {
                    std::cout << "Cannot access! Staying at current square" << std::endl;
                    map->moveWest();
                }
            }
            if (currentMap) {
                currentMap->handleCurrentSquare();
            } else {
                std::cout << "No valid map to handle." << std::endl;
            }
        } else if (command == "stay") {
            BaseMap* currentMap = processUserChoice(map, game, mapNumber);
            if (currentMap) {
                currentMap->handleCurrentSquare();
            } else {
                std::cout << "No valid map to handle." << std::endl;
            }
        } else if (command == "use" && subCommand == "item") {
            try {
                if (item == "apple") {
                    game->useItemByName("apple"); 
                } else if (item == "smallhealthpotion") {
                    game->useItemByName("smallhealthpotion"); 
                } else if (item == "healthpotion") {
                    game->useItemByName("healthpotion"); 
                } else if (item == "bighealthpotion") {
                    game->useItemByName("bighealthpotion"); 
                } else {
                    throw std::invalid_argument("Item does not exist: " + item);
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (!command.empty() && command[0] == '/') {
            try { 
                if (!command.empty() && command[0] == '/') {
                    if (command == "/stats" || command == "/s" || command == "/health" || command == "/h") {
                        game->displayStats();
                    } else if (command == "/displayinventory" || command == "/i" || command == "/inventory")  {
                        if (subCommand == "name") {
                            game->displayInventory(subCommand);
                        } else if (subCommand == "count") {
                            game->displayInventory(subCommand);
                        } else {
                            game->displayInventory();
                        }
                    } else if (command == "/map" || command == "/m") {
                        game->displayTopics();
                        handleMapSelection(game, map, mapNumber);
                    } else if (command == "/help") {
                        std::cout << "==================================================\n";
                        std::cout << "/stats to check completed squares and your other stats\n";
                        std::cout << "/i to see your inventory, /i name to sort by name, or /i count to sort by count.\n";
                        std::cout << "/map to view the map\n";
                        std::cout << "==================================================\n";
                        std::cout << "movenorth movewest movesouth moveeast to navigate through a map (not case sensitive)!\n";
                        std::cout << "==================================================\n";
                    } else {
                        throw std::invalid_argument("Unrecognized command: " + command);
                    }
                } 
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else if (!command.empty()){
            std::cerr << "Error: Unrecognized game machanic: " << input << std::endl;
        }
    }
}

void checkStatus(std::shared_ptr<AdventureGame>& game) {
    while (isGameRunning) {
        if (game->returnHealth() <= 0) {
            std::cout << "You have DIED! All Progress Lost! Type Anything to quit game!" << std::endl;
            isGameRunning = false; 
        } else if (game->completedSquares > 10) {
            std::cout << "You have WON! Thanks for playing! Type Anything to quit game!" << std::endl;
            isGameRunning = false; 
        }
        //returns after another user input
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main() {
    std::shared_ptr<BaseMap> map = std::make_shared<BaseMap>();
    std::shared_ptr<AdventureGame> game = std::make_shared<AdventureGame>();
    loadMaps(map, game);

    // std::shared_ptr<BaseMap> anotherMap = map;
    std::string mapNumber;

    auto displayInstructions = []() {
        std::cout << "\n";
        std::cout << "==================================================\n";
        std::cout << "\033[1mInstructions:\033[0m\n";
        std::cout << "- Explore \033[1m10 unique maps\033[0m, each with \033[1m9 unique squares\033[0m!\n";
        std::cout << "- Use \033[1m/map\033[0m to teleport to any map.\n";
        std::cout << "- Your position stays the \033[1mSAME\033[0m when teleporting. EX: (z,x,y): (0,1,2) -> (3,1,2).\n";
        std::cout << "- Beat the square's \033[1mBOSS\033[0m to progress. \033[1mUnbeaten squares RESET\033[0m if you leave!\n";
        std::cout << "- \033[1mProgress is stored\033[0m on each map if you beat the square. However, if you \033[1mDIE, YOU LOSE EVERYTHING\033[0m!\n";
        std::cout << "\n";
        std::cout << "- Strategize your teleports \033[1mwisely\033[0m and conquer the maps!\n";
        std::cout << "\n";
        std::cout << "\033[1mGood Luck, Tarnished!\033[0m\n";
        std::cout << "==================================================\n";
        std::cout << "Welcome to Nabeel's open world; Elden Ring Style Game! Full freedom to explore!\n";
        std::cout << "Let's start with /map to view and select a map to teleport to!: \n";
        std::cout << "/help for other commands! \n";
    };
    displayInstructions();

    std::thread inputThread1(commandListener, std::ref(game), std::ref(map), std::ref(mapNumber));
    std::thread inputThread2(checkStatus, std::ref(game));

    inputThread1.join();
    inputThread1.join();

    deleteMaps(); //clear maps

    return 0;
}
