#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
private:
    std::string name;
    int position;
    bool winner;

public:
    Player(std::string name);
    
    std::string getName() const;
    int getPosition() const;
    bool isWinner() const;
    
    void setPosition(int position);
    void setWinner(bool status);
    void displayInfo() const;
};

#endif 