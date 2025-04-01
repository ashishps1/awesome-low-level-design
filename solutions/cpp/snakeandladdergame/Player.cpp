#include "Player.hpp"
#include <iostream>

Player::Player(std::string name)
    : name(name), position(0), winner(false) {}

std::string Player::getName() const { return name; }
int Player::getPosition() const { return position; }
bool Player::isWinner() const { return winner; }

void Player::setPosition(int position) {
    this->position = position;
}

void Player::setWinner(bool status) {
    winner = status;
}

void Player::displayInfo() const {
    std::cout << "Player: " << name << std::endl;
    std::cout << "Position: " << position << std::endl;
    std::cout << "Status: " << (winner ? "Winner!" : "Playing") << std::endl;
} 