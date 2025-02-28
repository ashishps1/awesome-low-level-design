#ifndef DICE_HPP
#define DICE_HPP

class Dice {
private:
    int sides;

public:
    Dice(int sides = 6);
    int roll() const;
};

#endif 