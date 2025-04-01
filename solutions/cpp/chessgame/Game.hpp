#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"

class Game {
private:
    Board board;
    Color currentTurn;
    bool gameOver;

public:
    Game();
    
    void start();
    bool makeMove(Position from, Position to);
    void switchTurn();
    Color getCurrentTurn() const;
    bool isGameOver() const;
    void displayBoard() const;
};

#endif 