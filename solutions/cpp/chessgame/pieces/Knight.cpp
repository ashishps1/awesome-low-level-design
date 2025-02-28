#include "Knight.hpp"
#include <cstdlib>

Knight::Knight(Color color, Position position)
    : Piece(PieceType::KNIGHT, color, position) {}

bool Knight::isValidMove(Position newPosition, Piece* board[8][8]) const {
    if (!newPosition.isValid()) return false;
    
    Position currentPos = getPosition();
    int dx = abs(newPosition.getX() - currentPos.getX());
    int dy = abs(newPosition.getY() - currentPos.getY());
    
    // Knight moves in L-shape: 2 squares in one direction and 1 square perpendicular
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        Piece* targetPiece = board[newPosition.getX()][newPosition.getY()];
        return !targetPiece || targetPiece->getColor() != getColor();
    }
    
    return false;
} 