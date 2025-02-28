#ifndef PAWN_HPP
#define PAWN_HPP

#include "../Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

#endif 