#include "Board.hpp"
#include <iostream>
#include <iomanip>

Board::Board(int size) : size(size), EMPTY('-') {
    reset();
}

int Board::getSize() const { return size; }

char Board::getCell(int row, int col) const {
    return grid[row][col];
}

bool Board::isEmpty(int row, int col) const {
    return grid[row][col] == EMPTY;
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < size && col >= 0 && col < size;
}

bool Board::makeMove(int row, int col, char symbol) {
    if (!isValidPosition(row, col) || !isEmpty(row, col)) {
        return false;
    }
    grid[row][col] = symbol;
    return true;
}

bool Board::isFull() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (isEmpty(i, j)) return false;
        }
    }
    return true;
}

bool Board::checkWin(char symbol) const {
    return checkRows(symbol) || checkColumns(symbol) || checkDiagonals(symbol);
}

void Board::display() const {
    std::cout << "\nCurrent Board:" << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << std::setw(3) << grid[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::reset() {
    grid.resize(size, std::vector<char>(size, EMPTY));
}

bool Board::checkRows(char symbol) const {
    for (int i = 0; i < size; i++) {
        bool win = true;
        for (int j = 0; j < size; j++) {
            if (grid[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}

bool Board::checkColumns(char symbol) const {
    for (int j = 0; j < size; j++) {
        bool win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}

bool Board::checkDiagonals(char symbol) const {
    // Check main diagonal
    bool win = true;
    for (int i = 0; i < size; i++) {
        if (grid[i][i] != symbol) {
            win = false;
            break;
        }
    }
    if (win) return true;
    
    // Check other diagonal
    win = true;
    for (int i = 0; i < size; i++) {
        if (grid[i][size-1-i] != symbol) {
            win = false;
            break;
        }
    }
    return win;
} 