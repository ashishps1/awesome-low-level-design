#include "enemy.h"
#include <iostream>

Enemy::Enemy(const std::string& type, int health, double speed, bool armored, const std::string& weapon)
    : type(type), health(health), speed(speed), armored(armored), weapon(weapon) {}

Enemy* Enemy::clone() const {
    return new Enemy(type, health, speed, armored, weapon);
}

void Enemy::setHealth(int health) {
    this->health = health;
}

void Enemy::printStats() const {
    std::cout << type << " [Health: " << health 
              << ", Speed: " << speed 
              << ", Armored: " << (armored ? "true" : "false") 
              << ", Weapon: " << weapon << "]" << std::endl;
} 