#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>

class Board {
private:
    int size;
    std::map<int, int> snakes;    // start -> end
    std::map<int, int> ladders;   // start -> end

public:
    Board(int size = 100);
    
    int getSize() const;
    void addSnake(int start, int end);
    void addLadder(int start, int end);
    int getNextPosition(int currentPos) const;
    void displayInfo() const;
};

#endif 