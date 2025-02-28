#ifndef KING_HPP
#define KING_HPP

#include "../Piece.hpp"

class King : public Piece {
public:
    King(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

#endif 