// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Board;
class Player;
class Game;

// ===== Board.hpp =====
class Board {
private:
    vector<vector<char>> grid;
    const int size;
    const char EMPTY;

public:
    Board(int size = 3);
    
    int getSize() const;
    char getCell(int row, int col) const;
    bool isEmpty(int row, int col) const;
    bool isValidPosition(int row, int col) const;
    bool makeMove(int row, int col, char symbol);
    bool isFull() const;
    bool checkWin(char symbol) const;
    void display() const;
    void reset();

private:
    bool checkRows(char symbol) const;
    bool checkColumns(char symbol) const;
    bool checkDiagonals(char symbol) const;
};

// ===== Player.hpp =====
class Player {
private:
    string name;
    char symbol;
    bool isHuman;

public:
    Player(string name, char symbol, bool isHuman = true);
    
    string getName() const;
    char getSymbol() const;
    bool isHumanPlayer() const;
};

// ===== Game.hpp =====
class Game {
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    bool gameOver;

public:
    Game(int boardSize = 3);
    ~Game();
    
    void initializePlayers(const string& p1Name, const string& p2Name);
    void play();
    void makeMove(int row, int col);
    void switchPlayer();
    void displayResult() const;
    bool isGameOver() const;
    Player* getCurrentPlayer() const;

private:
    void computerMove();
    pair<int, int> findBestMove() const;
    int minimax(bool isMax, int depth) const;
};

// ===== Board.cpp =====
Board::Board(int size) : size(size), EMPTY('-') {
    reset();
}

int Board::getSize() const { return size; }

char Board::getCell(int row, int col) const {
    return grid[row][col];
}

bool Board::isEmpty(int row, int col) const {
    return grid[row][col] == EMPTY;
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < size && col >= 0 && col < size;
}

bool Board::makeMove(int row, int col, char symbol) {
    if (!isValidPosition(row, col) || !isEmpty(row, col)) {
        return false;
    }
    grid[row][col] = symbol;
    return true;
}

bool Board::isFull() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (isEmpty(i, j)) return false;
        }
    }
    return true;
}

bool Board::checkWin(char symbol) const {
    return checkRows(symbol) || checkColumns(symbol) || checkDiagonals(symbol);
}

void Board::display() const {
    cout << "\nCurrent Board:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(3) << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Board::reset() {
    grid.resize(size, vector<char>(size, EMPTY));
}

bool Board::checkRows(char symbol) const {
    for (int i = 0; i < size; i++) {
        bool win = true;
        for (int j = 0; j < size; j++) {
            if (grid[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}

bool Board::checkColumns(char symbol) const {
    for (int j = 0; j < size; j++) {
        bool win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}

bool Board::checkDiagonals(char symbol) const {
    // Check main diagonal
    bool win = true;
    for (int i = 0; i < size; i++) {
        if (grid[i][i] != symbol) {
            win = false;
            break;
        }
    }
    if (win) return true;
    
    // Check other diagonal
    win = true;
    for (int i = 0; i < size; i++) {
        if (grid[i][size-1-i] != symbol) {
            win = false;
            break;
        }
    }
    return win;
} 

// ===== Game.cpp =====
Game::Game(int boardSize) : board(boardSize), gameOver(false) {
    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = nullptr;
    srand(static_cast<unsigned int>(time(nullptr)));
}

Game::~Game() {
    delete player1;
    delete player2;
}

void Game::initializePlayers(const string& p1Name, const string& p2Name) {
    player1 = new Player(p1Name, 'X');
    player2 = new Player(p2Name, 'O', false);  // Computer player
    currentPlayer = player1;
}

void Game::play() {
    while (!gameOver) {
        board.display();
        
        if (currentPlayer->isHumanPlayer()) {
            int row, col;
            cout << currentPlayer->getName() << "'s turn (symbol: "
                      << currentPlayer->getSymbol() << ")" << endl;
            cout << "Enter row (0-" << board.getSize()-1 << "): ";
            cin >> row;
            cout << "Enter column (0-" << board.getSize()-1 << "): ";
            cin >> col;
            
            makeMove(row, col);
        } else {
            cout << "Computer's turn..." << endl;
            computerMove();
        }
    }
    
    displayResult();
}

void Game::makeMove(int row, int col) {
    if (!board.isValidPosition(row, col)) {
        cout << "Invalid position!" << endl;
        return;
    }
    
    if (!board.isEmpty(row, col)) {
        cout << "Position already taken!" << endl;
        return;
    }
    
    board.makeMove(row, col, currentPlayer->getSymbol());
    
    if (board.checkWin(currentPlayer->getSymbol())) {
        gameOver = true;
        return;
    }
    
    if (board.isFull()) {
        gameOver = true;
        currentPlayer = nullptr;
        return;
    }
    
    switchPlayer();
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

void Game::displayResult() const {
    board.display();
    if (currentPlayer) {
        cout << currentPlayer->getName() << " wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }
}

bool Game::isGameOver() const {
    return gameOver;
}

Player* Game::getCurrentPlayer() const {
    return currentPlayer;
}

void Game::computerMove() {
    auto [row, col] = findBestMove();
    makeMove(row, col);
}

pair<int, int> Game::findBestMove() const {
    int bestScore = numeric_limits<int>::min();
    pair<int, int> bestMove = {0, 0};
    
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.isEmpty(i, j)) {
                Board tempBoard = board;  // Create a copy
                tempBoard.makeMove(i, j, player2->getSymbol());
                
                int score = minimax(false, 0);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    
    return bestMove;
}

int Game::minimax(bool isMax, int depth) const {
    if (board.checkWin(player2->getSymbol())) return 10 - depth;
    if (board.checkWin(player1->getSymbol())) return depth - 10;
    if (board.isFull()) return 0;
    
    int bestScore = isMax ? numeric_limits<int>::min() : numeric_limits<int>::max();
    
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.isEmpty(i, j)) {
                Board tempBoard = board;  // Create a copy
                tempBoard.makeMove(i, j, isMax ? player2->getSymbol() : player1->getSymbol());
                
                int score = minimax(!isMax, depth + 1);
                bestScore = isMax ? max(score, bestScore) : min(score, bestScore);
            }
        }
    }
    
    return bestScore;
} 

// ===== Player.cpp =====
Player::Player(string name, char symbol, bool isHuman)
    : name(name), symbol(symbol), isHuman(isHuman) {}

string Player::getName() const { return name; }
char Player::getSymbol() const { return symbol; }
bool Player::isHumanPlayer() const { return isHuman; } 

// ===== TicTacToeDemo.cpp =====
int main() {
    cout << "Welcome to Tic Tac Toe!" << endl;
    
    Game game;
    game.initializePlayers("Human", "Computer");
    game.play();
    
    return 0;
} 

