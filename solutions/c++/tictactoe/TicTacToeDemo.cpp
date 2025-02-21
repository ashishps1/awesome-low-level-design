#include "Game.hpp"
#include <iostream>

int main() {
    std::cout << "Welcome to Tic Tac Toe!" << std::endl;
    
    Game game;
    game.initializePlayers("Human", "Computer");
    game.play();
    
    return 0;
} 