#include "Game.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

Game::Game(int boardSize) : board(boardSize), gameOver(false) {
    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = nullptr;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::initializePlayers(const std::string& p1Name, const std::string& p2Name) {
    player1 = new Player(p1Name, 'X');
    player2 = new Player(p2Name, 'O', false);  // Computer player
    currentPlayer = player1;
}

void Game::play() {
    while (!gameOver) {
        board.display();
        
        if (currentPlayer->isHumanPlayer()) {
            int row, col;
            std::cout << currentPlayer->getName() << "'s turn (symbol: "
                      << currentPlayer->getSymbol() << ")" << std::endl;
            std::cout << "Enter row (0-" << board.getSize()-1 << "): ";
            std::cin >> row;
            std::cout << "Enter column (0-" << board.getSize()-1 << "): ";
            std::cin >> col;
            
            makeMove(row, col);
        } else {
            std::cout << "Computer's turn..." << std::endl;
            computerMove();
        }
    }
    
    displayResult();
}

void Game::makeMove(int row, int col) {
    if (!board.isValidPosition(row, col)) {
        std::cout << "Invalid position!" << std::endl;
        return;
    }
    
    if (!board.isEmpty(row, col)) {
        std::cout << "Position already taken!" << std::endl;
        return;
    }
    
    board.makeMove(row, col, currentPlayer->getSymbol());
    
    if (board.checkWin(currentPlayer->getSymbol())) {
        gameOver = true;
        return;
    }
    
    if (board.isFull()) {
        gameOver = true;
        currentPlayer = nullptr;
        return;
    }
    
    switchPlayer();
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

void Game::displayResult() const {
    board.display();
    if (currentPlayer) {
        std::cout << currentPlayer->getName() << " wins!" << std::endl;
    } else {
        std::cout << "It's a draw!" << std::endl;
    }
}

bool Game::isGameOver() const {
    return gameOver;
}

Player* Game::getCurrentPlayer() const {
    return currentPlayer;
}

void Game::computerMove() {
    auto [row, col] = findBestMove();
    makeMove(row, col);
}

std::pair<int, int> Game::findBestMove() const {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {0, 0};
    
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.isEmpty(i, j)) {
                Board tempBoard = board;  // Create a copy
                tempBoard.makeMove(i, j, player2->getSymbol());
                
                int score = minimax(false, 0);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    
    return bestMove;
}

int Game::minimax(bool isMax, int depth) const {
    if (board.checkWin(player2->getSymbol())) return 10 - depth;
    if (board.checkWin(player1->getSymbol())) return depth - 10;
    if (board.isFull()) return 0;
    
    int bestScore = isMax ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.isEmpty(i, j)) {
                Board tempBoard = board;  // Create a copy
                tempBoard.makeMove(i, j, isMax ? player2->getSymbol() : player1->getSymbol());
                
                int score = minimax(!isMax, depth + 1);
                bestScore = isMax ? std::max(score, bestScore) : std::min(score, bestScore);
            }
        }
    }
    
    return bestScore;
} 