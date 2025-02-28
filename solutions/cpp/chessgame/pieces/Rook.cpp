#include "Rook.hpp"
#include <cstdlib>

Rook::Rook(Color color, Position position)
    : Piece(PieceType::ROOK, color, position) {}

bool Rook::isValidMove(Position newPosition, Piece* board[8][8]) const {
    if (!newPosition.isValid()) return false;
    
    Position currentPos = getPosition();
    int dx = newPosition.getX() - currentPos.getX();
    int dy = newPosition.getY() - currentPos.getY();
    
    // Rook can only move horizontally or vertically
    if (dx == 0 || dy == 0) {
        // Check if path is clear
        int xStep = (dx == 0) ? 0 : dx / abs(dx);
        int yStep = (dy == 0) ? 0 : dy / abs(dy);
        
        int x = currentPos.getX() + xStep;
        int y = currentPos.getY() + yStep;
        
        while (x != newPosition.getX() || y != newPosition.getY()) {
            if (board[x][y] != nullptr) return false;
            x += xStep;
            y += yStep;
        }
        
        Piece* targetPiece = board[newPosition.getX()][newPosition.getY()];
        return !targetPiece || targetPiece->getColor() != getColor();
    }
    
    return false;
} 