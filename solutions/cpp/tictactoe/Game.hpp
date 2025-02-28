#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Player.hpp"

class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    bool gameOver;

public:
    Game(int boardSize = 3);
    ~Game();
    
    void initializePlayers(const std::string& p1Name, const std::string& p2Name);
    void play();
    void makeMove(int row, int col);
    void switchPlayer();
    void displayResult() const;
    bool isGameOver() const;
    Player* getCurrentPlayer() const;

private:
    void computerMove();
    std::pair<int, int> findBestMove() const;
    int minimax(bool isMax, int depth) const;
};

#endif 