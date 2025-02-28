#include "Piece.hpp"
#include <cctype>

Piece::Piece(PieceType type, Color color, Position position)
    : type(type), color(color), position(position), captured(false) {}

PieceType Piece::getType() const { return type; }
Color Piece::getColor() const { return color; }
Position Piece::getPosition() const { return position; }
bool Piece::isCaptured() const { return captured; }

void Piece::setPosition(Position newPosition) { position = newPosition; }
void Piece::setCaptured(bool status) { captured = status; }

std::string Piece::getSymbol() const {
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