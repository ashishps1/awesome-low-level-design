#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "../Piece.hpp"

class Bishop : public Piece {
public:
    Bishop(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

#endif 