#ifndef BOARD_HPP
#define BOARD_HPP

#include "Piece.hpp"
#include <vector>

class Board {
private:
    Piece* squares[8][8];
    std::vector<Piece*> capturedPieces;

public:
    Board();
    ~Board();
    
    void initialize();
    bool movePiece(Position from, Position to);
    Piece* getPiece(Position position) const;
    void displayBoard() const;
    
private:
    void placePiece(Piece* piece);
    void setupInitialPosition();
};

#endif 