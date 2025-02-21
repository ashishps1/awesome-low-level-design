#include "Board.hpp"
#include <iostream>

Board::Board(int size) : size(size) {}

int Board::getSize() const { return size; }

void Board::addSnake(int start, int end) {
    if (start > end && start < size) {
        snakes[start] = end;
    }
}

void Board::addLadder(int start, int end) {
    if (end > start && end <= size) {
        ladders[start] = end;
    }
}

int Board::getNextPosition(int currentPos) const {
    // Check for snakes
    auto snakeIt = snakes.find(currentPos);
    if (snakeIt != snakes.end()) {
        std::cout << "Oops! Snake at position " << currentPos 
                  << ". Moving down to " << snakeIt->second << std::endl;
        return snakeIt->second;
    }
    
    // Check for ladders
    auto ladderIt = ladders.find(currentPos);
    if (ladderIt != ladders.end()) {
        std::cout << "Yay! Ladder at position " << currentPos 
                  << ". Moving up to " << ladderIt->second << std::endl;
        return ladderIt->second;
    }
    
    return currentPos;
}

void Board::displayInfo() const {
    std::cout << "\nBoard Information:" << std::endl;
    std::cout << "Size: " << size << " squares" << std::endl;
    
    std::cout << "\nSnakes:" << std::endl;
    for (const auto& snake : snakes) {
        std::cout << "From " << snake.first << " to " << snake.second << std::endl;
    }
    
    std::cout << "\nLadders:" << std::endl;
    for (const auto& ladder : ladders) {
        std::cout << "From " << ladder.first << " to " << ladder.second << std::endl;
    }
} 