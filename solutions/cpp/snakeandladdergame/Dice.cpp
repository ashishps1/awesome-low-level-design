#include "Dice.hpp"
#include <random>
#include <ctime>

Dice::Dice(int sides) : sides(sides) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Dice::roll() const {
    return (std::rand() % sides) + 1;
} 