#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Board.hpp"
#include "Player.hpp"
#include "Dice.hpp"

class Game {
private:
    Board board;
    std::vector<Player*> players;
    Dice dice;
    int currentPlayerIndex;
    bool gameOver;

public:
    Game(int boardSize = 100);
    ~Game();
    
    void addPlayer(const std::string& name);
    void setupBoard();
    bool makeMove();
    void play();
    void displayStatus() const;
    
private:
    void movePlayer(Player* player, int steps);
    bool checkWin(Player* player) const;
    Player* getCurrentPlayer() const;
};

#endif 