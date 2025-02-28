#include "King.hpp"
#include <cstdlib>

King::King(Color color, Position position)
    : Piece(PieceType::KING, color, position) {}

bool King::isValidMove(Position newPosition, Piece* board[8][8]) const {
    if (!newPosition.isValid()) return false;
    
    Position currentPos = getPosition();
    int dx = abs(newPosition.getX() - currentPos.getX());
    int dy = abs(newPosition.getY() - currentPos.getY());
    
    // King can move one square in any direction
    if (dx <= 1 && dy <= 1) {
        Piece* targetPiece = board[newPosition.getX()][newPosition.getY()];
        return !targetPiece || targetPiece->getColor() != getColor();
    }
    
    return false;
} 