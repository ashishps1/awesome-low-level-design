#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "../Piece.hpp"

class Queen : public Piece {
public:
    Queen(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

#endif 