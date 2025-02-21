#ifndef ROOK_HPP
#define ROOK_HPP

#include "../Piece.hpp"

class Rook : public Piece {
public:
    Rook(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

#endif 