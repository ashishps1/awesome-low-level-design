#pragma once
#include "enemy_prototype.h"
#include <string>

class Enemy : public EnemyPrototype {
public:
    Enemy(const std::string& type, int health, double speed, bool armored, const std::string& weapon);
    
    // Clone method implementation
    Enemy* clone() const override;
    
    // Setter for health
    void setHealth(int health);
    
    // Print enemy stats
    void printStats() const;

private:
    std::string type;
    int health;
    double speed;
    bool armored;
    std::string weapon;
}; 