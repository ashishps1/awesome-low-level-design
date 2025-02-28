#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

class Player {
private:
    std::string name;
    char symbol;
    bool isHuman;

public:
    Player(std::string name, char symbol, bool isHuman = true);
    
    std::string getName() const;
    char getSymbol() const;
    bool isHumanPlayer() const;
};

#endif 