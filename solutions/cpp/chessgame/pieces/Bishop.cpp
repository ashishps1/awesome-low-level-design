#include "Bishop.hpp"
#include <cstdlib>

Bishop::Bishop(Color color, Position position)
    : Piece(PieceType::BISHOP, color, position) {}

bool Bishop::isValidMove(Position newPosition, Piece* board[8][8]) const {
    if (!newPosition.isValid()) return false;
    
    Position currentPos = getPosition();
    int dx = newPosition.getX() - currentPos.getX();
    int dy = newPosition.getY() - currentPos.getY();
    
    // Bishop can only move diagonally
    if (abs(dx) == abs(dy)) {
        // Check if path is clear
        int xStep = dx / abs(dx);
        int yStep = dy / abs(dy);
        
        int x = currentPos.getX() + xStep;
        int y = currentPos.getY() + yStep;
        
        while (x != newPosition.getX()) {
            if (board[x][y] != nullptr) return false;
            x += xStep;
            y += yStep;
        }
        
        Piece* targetPiece = board[newPosition.getX()][newPosition.getY()];
        return !targetPiece || targetPiece->getColor() != getColor();
    }
    
    return false;
} 