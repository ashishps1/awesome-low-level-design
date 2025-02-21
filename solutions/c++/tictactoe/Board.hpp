#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>

class Board {
private:
    std::vector<std::vector<char>> grid;
    const int size;
    const char EMPTY;

public:
    Board(int size = 3);
    
    int getSize() const;
    char getCell(int row, int col) const;
    bool isEmpty(int row, int col) const;
    bool isValidPosition(int row, int col) const;
    bool makeMove(int row, int col, char symbol);
    bool isFull() const;
    bool checkWin(char symbol) const;
    void display() const;
    void reset();

private:
    bool checkRows(char symbol) const;
    bool checkColumns(char symbol) const;
    bool checkDiagonals(char symbol) const;
};

#endif 