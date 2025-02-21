#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "../Piece.hpp"

class Knight : public Piece {
public:
    Knight(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

#endif 