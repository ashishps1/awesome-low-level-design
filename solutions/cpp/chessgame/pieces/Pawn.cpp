#include "Pawn.hpp"

Pawn::Pawn(Color color, Position position)
    : Piece(PieceType::PAWN, color, position) {}

bool Pawn::isValidMove(Position newPosition, Piece* board[8][8]) const {
    if (!newPosition.isValid()) return false;
    
    Position currentPos = getPosition();
    int direction = (getColor() == Color::WHITE) ? 1 : -1;
    int dx = newPosition.getX() - currentPos.getX();
    int dy = newPosition.getY() - currentPos.getY();
    
    // Normal move forward
    if (dy == 0 && dx == direction) {
        return board[newPosition.getX()][newPosition.getY()] == nullptr;
    }
    
    // Initial two-square move
    if (dy == 0 && dx == 2 * direction && 
        ((getColor() == Color::WHITE && currentPos.getX() == 1) ||
         (getColor() == Color::BLACK && currentPos.getX() == 6))) {
        return board[currentPos.getX() + direction][currentPos.getY()] == nullptr &&
               board[newPosition.getX()][newPosition.getY()] == nullptr;
    }
    
    // Capture diagonally
    if (abs(dy) == 1 && dx == direction) {
        Piece* targetPiece = board[newPosition.getX()][newPosition.getY()];
        return targetPiece && targetPiece->getColor() != getColor();
    }
    
    return false;
} 