#include "Player.hpp"

Player::Player(std::string name, char symbol, bool isHuman)
    : name(name), symbol(symbol), isHuman(isHuman) {}

std::string Player::getName() const { return name; }
char Player::getSymbol() const { return symbol; }
bool Player::isHumanPlayer() const { return isHuman; } 