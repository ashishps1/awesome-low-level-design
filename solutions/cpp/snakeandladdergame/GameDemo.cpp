#include "Game.hpp"
#include <iostream>

int main() {
    Game game;
    
    // Add players
    game.addPlayer("Player 1");
    game.addPlayer("Player 2");
    game.addPlayer("Player 3");
    
    // Setup board with snakes and ladders
    game.setupBoard();
    
    // Start the game
    game.play();
    
    return 0;
} 