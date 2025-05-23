#pragma once
#include "enemy.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>

class EnemyRegistry {
public:
    void registerPrototype(const std::string& key, std::unique_ptr<Enemy> prototype);
    std::unique_ptr<Enemy> get(const std::string& key) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Enemy>> prototypes;
}; 