#pragma once

class EnemyPrototype {
public:
    virtual ~EnemyPrototype() = default;
    virtual EnemyPrototype* clone() const = 0;
}; 