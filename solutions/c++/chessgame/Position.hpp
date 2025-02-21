#ifndef POSITION_HPP
#define POSITION_HPP

class Position {
private:
    int x;
    int y;

public:
    Position(int x, int y);
    
    int getX() const;
    int getY() const;
    bool isValid() const;
    bool operator==(const Position& other) const;
};

#endif 