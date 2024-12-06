#ifndef BASE_MAP_H
#define BASE_MAP_H

#include "maingame.h"
#include <vector>
#include <utility>
#include <string>
#include <queue>

typedef std::pair<int, int> location; 
class BaseMap : public AdventureGame {
protected:
    std::pair<int, int> playerPosition; //track the player's current position
    std::queue<std::string> input;

public:
    BaseMap();                       
    virtual ~BaseMap();     

    void startInputListener(); 
    void displayWithDelay(const std::string& message, int delayMs = 20); 

    void displayMapWithPlayer(const std::array<std::array<bool, 3>, 3>& squares);

    std::string getCurrentInput(); 
    void moveNorth();          
    void moveSouth();               
    void moveWest();                 
    void moveEast(); 
    virtual void handleCurrentSquare() {return;}; 
    location getCurrentLocaiton();             
    void printChoices(const std::string& choosewhat = "option", const std::string& choice1 = "", const std::string& choice2 = "", const std::string& choice3 = "", const std::string& choice4 = "");
    bool validateChoice(const std::string& choice, 
                    const std::string& rightChoice, 
                    const std::string& winningMessage = "That's right! Congrats you did not lose any health!", 
                    const std::string& losingMessage = "Wrong!", 
                    const std::shared_ptr<BaseMap>& existingBaseMap = nullptr);
    virtual bool uncompletedSquare() {return false;};
};

#endif
