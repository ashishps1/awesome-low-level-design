#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include "Position.hpp"

enum class PieceType {
    KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN
};

enum class Color {
    WHITE, BLACK
};

class Piece {
private:
    PieceType type;
    Color color;
    Position position;
    bool captured;

public:
    Piece(PieceType type, Color color, Position position)
        : type(type), color(color), position(position), captured(false) {}
    
    virtual ~Piece() = default;
    
    PieceType getType() const { return type; }
    Color getColor() const { return color; }
    Position getPosition() const { return position; }
    bool isCaptured() const { return captured; }
    
    void setPosition(Position newPosition) { position = newPosition; }
    void setCaptured(bool status) { captured = status; }
    
    virtual bool isValidMove(Position newPosition, Piece* board[8][8]) const = 0;
    
    std::string getSymbol() const {
        char symbol;
        switch (type) {
            case PieceType::KING: symbol = 'K'; break;
            case PieceType::QUEEN: symbol = 'Q'; break;
            case PieceType::BISHOP: symbol = 'B'; break;
            case PieceType::KNIGHT: symbol = 'N'; break;
            case PieceType::ROOK: symbol = 'R'; break;
            case PieceType::PAWN: symbol = 'P'; break;
            default: symbol = '?';
        }
        return std::string(1, color == Color::WHITE ? symbol : tolower(symbol));
    }
};

#endif 