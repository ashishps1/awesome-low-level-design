// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
//
// The original chessgame source was incomplete/broken, so two fixes were made
// here to make it actually compile, link and run:
//   1. Piece.cpp was dropped — it redefined methods already defined inline in
//      Piece.hpp (an ODR redefinition error).
//   2. Position and Board had declared-but-never-defined methods (no Position.cpp
//      / Board.cpp existed in the repo). Faithful implementations were added
//      below (see the "added: missing from original source" sections).
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Position;
class Piece;
class Bishop;
class Board;
class Game;
class King;
class Knight;
class Pawn;
class Queen;
class Rook;

// ===== Position.hpp =====
class Position {
private:
    int x;
    int y;

public:
    Position(int x, int y);
    
    int getX() const;
    int getY() const;
    bool isValid() const;
    bool operator==(const Position& other) const;
};

// ===== Piece.hpp =====
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
    
    string getSymbol() const {
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
        return string(1, color == Color::WHITE ? symbol : tolower(symbol));
    }
};

// ===== Bishop.hpp =====
class Bishop : public Piece {
public:
    Bishop(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

// ===== Board.hpp =====
class Board {
private:
    Piece* squares[8][8];
    vector<Piece*> capturedPieces;

public:
    Board();
    ~Board();
    
    void initialize();
    bool movePiece(Position from, Position to);
    Piece* getPiece(Position position) const;
    void displayBoard() const;
    
private:
    void placePiece(Piece* piece);
    void setupInitialPosition();
};

// ===== Game.hpp =====
class Game {
private:
    Board board;
    Color currentTurn;
    bool gameOver;

public:
    Game();
    
    void start();
    bool makeMove(Position from, Position to);
    void switchTurn();
    Color getCurrentTurn() const;
    bool isGameOver() const;
    void displayBoard() const;
};

// ===== King.hpp =====
class King : public Piece {
public:
    King(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

// ===== Knight.hpp =====
class Knight : public Piece {
public:
    Knight(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

// ===== Pawn.hpp =====
class Pawn : public Piece {
public:
    Pawn(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

// ===== Queen.hpp =====
class Queen : public Piece {
public:
    Queen(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

// ===== Rook.hpp =====
class Rook : public Piece {
public:
    Rook(Color color, Position position);
    bool isValidMove(Position newPosition, Piece* board[8][8]) const override;
};

// ===== Game.cpp =====
Game::Game() : currentTurn(Color::WHITE), gameOver(false) {
    board.initialize();
}

void Game::start() {
    while (!gameOver) {
        displayBoard();
        
        cout << (currentTurn == Color::WHITE ? "White" : "Black") << "'s turn" << endl;
        
        int fromX, fromY, toX, toY;
        cout << "Enter move (fromX fromY toX toY): ";
        cin >> fromX >> fromY >> toX >> toY;
        
        Position from(fromX, fromY);
        Position to(toX, toY);
        
        if (makeMove(from, to)) {
            switchTurn();
        } else {
            cout << "Invalid move! Try again." << endl;
        }
    }
}

bool Game::makeMove(Position from, Position to) {
    Piece* piece = board.getPiece(from);
    if (!piece || piece->getColor() != currentTurn) return false;
    
    return board.movePiece(from, to);
}

void Game::switchTurn() {
    currentTurn = (currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
}

Color Game::getCurrentTurn() const {
    return currentTurn;
}

bool Game::isGameOver() const {
    return gameOver;
}

void Game::displayBoard() const {
    board.displayBoard();
} 

// ===== Bishop.cpp =====
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

// ===== King.cpp =====
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

// ===== Knight.cpp =====
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

// ===== Pawn.cpp =====
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

// ===== Queen.cpp =====
Queen::Queen(Color color, Position position)
    : Piece(PieceType::QUEEN, color, position) {}

bool Queen::isValidMove(Position newPosition, Piece* board[8][8]) const {
    if (!newPosition.isValid()) return false;
    
    Position currentPos = getPosition();
    int dx = newPosition.getX() - currentPos.getX();
    int dy = newPosition.getY() - currentPos.getY();
    
    // Queen can move diagonally, horizontally, or vertically
    if (abs(dx) == abs(dy) || dx == 0 || dy == 0) {
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

// ===== Rook.cpp =====
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

// ===== Position.cpp (added: missing from original source) =====
Position::Position(int x, int y) : x(x), y(y) {}
int Position::getX() const { return x; }
int Position::getY() const { return y; }
bool Position::isValid() const { return x >= 0 && x < 8 && y >= 0 && y < 8; }
bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

// ===== Board.cpp (added: missing from original source) =====
Board::Board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            squares[i][j] = nullptr;
}

Board::~Board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            delete squares[i][j];
    for (Piece* p : capturedPieces)
        delete p;
}

void Board::placePiece(Piece* piece) {
    Position pos = piece->getPosition();
    squares[pos.getX()][pos.getY()] = piece;
}

void Board::setupInitialPosition() {
    // Back-rank order by column: R N B Q K B N R
    PieceType order[8] = {
        PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN,
        PieceType::KING, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK
    };
    auto makePiece = [](PieceType t, Color c, Position p) -> Piece* {
        switch (t) {
            case PieceType::ROOK:   return new Rook(c, p);
            case PieceType::KNIGHT: return new Knight(c, p);
            case PieceType::BISHOP: return new Bishop(c, p);
            case PieceType::QUEEN:  return new Queen(c, p);
            case PieceType::KING:   return new King(c, p);
            case PieceType::PAWN:   return new Pawn(c, p);
        }
        return nullptr;
    };

    // White occupies rows 0 (back rank) and 1 (pawns); black rows 7 and 6.
    for (int col = 0; col < 8; ++col) {
        placePiece(makePiece(order[col], Color::WHITE, Position(0, col)));
        placePiece(new Pawn(Color::WHITE, Position(1, col)));
        placePiece(new Pawn(Color::BLACK, Position(6, col)));
        placePiece(makePiece(order[col], Color::BLACK, Position(7, col)));
    }
}

void Board::initialize() {
    setupInitialPosition();
}

Piece* Board::getPiece(Position position) const {
    if (!position.isValid()) return nullptr;
    return squares[position.getX()][position.getY()];
}

bool Board::movePiece(Position from, Position to) {
    if (!from.isValid() || !to.isValid()) return false;
    Piece* piece = squares[from.getX()][from.getY()];
    if (!piece) return false;
    if (!piece->isValidMove(to, squares)) return false;

    Piece* target = squares[to.getX()][to.getY()];
    if (target) {
        if (target->getColor() == piece->getColor()) return false; // no friendly capture
        target->setCaptured(true);
        capturedPieces.push_back(target);
    }

    squares[to.getX()][to.getY()] = piece;
    squares[from.getX()][from.getY()] = nullptr;
    piece->setPosition(to);
    return true;
}

void Board::displayBoard() const {
    for (int i = 7; i >= 0; --i) {
        cout << i << " ";
        for (int j = 0; j < 8; ++j) {
            if (squares[i][j])
                cout << squares[i][j]->getSymbol() << " ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << "  0 1 2 3 4 5 6 7" << endl;
}

// ===== ChessDemo.cpp =====
int main() {
    Game chess;
    cout << "Welcome to Chess!" << endl;
    chess.start();
    return 0;
} 

