#include "Game.hpp"
#include <iostream>
#include <thread>
#include <chrono>

Game::Game(int boardSize) : board(boardSize), currentPlayerIndex(0), gameOver(false) {}

Game::~Game() {
    for (auto player : players) {
        delete player;
    }
}

void Game::addPlayer(const std::string& name) {
    players.push_back(new Player(name));
}

void Game::setupBoard() {
    // Add snakes
    board.addSnake(99, 10);
    board.addSnake(95, 75);
    board.addSnake(92, 88);
    board.addSnake(89, 68);
    board.addSnake(74, 53);
    board.addSnake(62, 19);
    board.addSnake(46, 25);
    board.addSnake(49, 11);
    
    // Add ladders
    board.addLadder(2, 38);
    board.addLadder(7, 14);
    board.addLadder(8, 31);
    board.addLadder(15, 26);
    board.addLadder(21, 42);
    board.addLadder(28, 84);
    board.addLadder(36, 44);
    board.addLadder(51, 67);
    board.addLadder(71, 91);
    board.addLadder(78, 98);
    
    board.displayInfo();
}

bool Game::makeMove() {
    if (gameOver || players.empty()) return false;
    
    Player* currentPlayer = getCurrentPlayer();
    std::cout << "\n" << currentPlayer->getName() << "'s turn" << std::endl;
    
    int roll = dice.roll();
    std::cout << "Rolled: " << roll << std::endl;
    
    movePlayer(currentPlayer, roll);
    
    if (checkWin(currentPlayer)) {
        currentPlayer->setWinner(true);
        gameOver = true;
        std::cout << "\nCongratulations! " << currentPlayer->getName() << " wins!" << std::endl;
        return false;
    }
    
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    return true;
}

void Game::play() {
    if (players.empty()) {
        std::cout << "No players in the game!" << std::endl;
        return;
    }
    
    std::cout << "\nStarting the game..." << std::endl;
    while (makeMove()) {
        displayStatus();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::displayStatus() const {
    std::cout << "\nCurrent Game Status:" << std::endl;
    for (const auto& player : players) {
        std::cout << player->getName() << " at position " << player->getPosition() << std::endl;
    }
}

void Game::movePlayer(Player* player, int steps) {
    int newPosition = player->getPosition() + steps;
    
    if (newPosition > board.getSize()) {
        std::cout << "Cannot move, need exact number to finish" << std::endl;
        return;
    }
    
    newPosition = board.getNextPosition(newPosition);
    player->setPosition(newPosition);
    
    std::cout << player->getName() << " moved to position " << newPosition << std::endl;
}

bool Game::checkWin(Player* player) const {
    return player->getPosition() == board.getSize();
}

Player* Game::getCurrentPlayer() const {
    return players[currentPlayerIndex];
} 