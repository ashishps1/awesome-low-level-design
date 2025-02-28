#include "Game.hpp"
#include <iostream>

Game::Game() : currentTurn(Color::WHITE), gameOver(false) {
    board.initialize();
}

void Game::start() {
    while (!gameOver) {
        displayBoard();
        
        std::cout << (currentTurn == Color::WHITE ? "White" : "Black") << "'s turn" << std::endl;
        
        int fromX, fromY, toX, toY;
        std::cout << "Enter move (fromX fromY toX toY): ";
        std::cin >> fromX >> fromY >> toX >> toY;
        
        Position from(fromX, fromY);
        Position to(toX, toY);
        
        if (makeMove(from, to)) {
            switchTurn();
        } else {
            std::cout << "Invalid move! Try again." << std::endl;
        }
    }
}

bool Game::makeMove(Position from, Position to) {
    Piece* piece = board.getPiece(from);
    if (!piece || piece->getColor() != currentTurn) return false;
    
    return board.movePiece(from, to);
}

void Game::switchTurn() {
    currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

Color Game::getCurrentTurn() const {
    return currentTurn;
}

bool Game::isGameOver() const {
    return gameOver;
}

void Game::displayBoard() const {
    board.displayBoard();
} 