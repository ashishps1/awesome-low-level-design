// Single-file build (no header files) — merged from the multi-file project.
// Build & run:  g++ -std=c++17 main.cpp -o app && ./app
#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// ----- forward declarations -----
class Board;
class Dice;
class Player;
class Game;

// ===== Board.hpp =====
class Board {
private:
    int size;
    map<int, int> snakes;    // start -> end
    map<int, int> ladders;   // start -> end

public:
    Board(int size = 100);
    
    int getSize() const;
    void addSnake(int start, int end);
    void addLadder(int start, int end);
    int getNextPosition(int currentPos) const;
    void displayInfo() const;
};

// ===== Dice.hpp =====
class Dice {
private:
    int sides;

public:
    Dice(int sides = 6);
    int roll() const;
};

// ===== Player.hpp =====
class Player {
private:
    string name;
    int position;
    bool winner;

public:
    Player(string name);
    
    string getName() const;
    int getPosition() const;
    bool isWinner() const;
    
    void setPosition(int position);
    void setWinner(bool status);
    void displayInfo() const;
};

// ===== Game.hpp =====
class Game {
private:
    Board board;
    vector<Player*> players;
    Dice dice;
    int currentPlayerIndex;
    bool gameOver;

public:
    Game(int boardSize = 100);
    ~Game();
    
    void addPlayer(const string& name);
    void setupBoard();
    bool makeMove();
    void play();
    void displayStatus() const;
    
private:
    void movePlayer(Player* player, int steps);
    bool checkWin(Player* player) const;
    Player* getCurrentPlayer() const;
};

// ===== Board.cpp =====
Board::Board(int size) : size(size) {}

int Board::getSize() const { return size; }

void Board::addSnake(int start, int end) {
    if (start > end && start < size) {
        snakes[start] = end;
    }
}

void Board::addLadder(int start, int end) {
    if (end > start && end <= size) {
        ladders[start] = end;
    }
}

int Board::getNextPosition(int currentPos) const {
    // Check for snakes
    auto snakeIt = snakes.find(currentPos);
    if (snakeIt != snakes.end()) {
        cout << "Oops! Snake at position " << currentPos 
                  << ". Moving down to " << snakeIt->second << endl;
        return snakeIt->second;
    }
    
    // Check for ladders
    auto ladderIt = ladders.find(currentPos);
    if (ladderIt != ladders.end()) {
        cout << "Yay! Ladder at position " << currentPos 
                  << ". Moving up to " << ladderIt->second << endl;
        return ladderIt->second;
    }
    
    return currentPos;
}

void Board::displayInfo() const {
    cout << "\nBoard Information:" << endl;
    cout << "Size: " << size << " squares" << endl;
    
    cout << "\nSnakes:" << endl;
    for (const auto& snake : snakes) {
        cout << "From " << snake.first << " to " << snake.second << endl;
    }
    
    cout << "\nLadders:" << endl;
    for (const auto& ladder : ladders) {
        cout << "From " << ladder.first << " to " << ladder.second << endl;
    }
} 

// ===== Dice.cpp =====
Dice::Dice(int sides) : sides(sides) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

int Dice::roll() const {
    return (rand() % sides) + 1;
} 

// ===== Game.cpp =====
Game::Game(int boardSize) : board(boardSize), currentPlayerIndex(0), gameOver(false) {}

Game::~Game() {
    for (auto player : players) {
        delete player;
    }
}

void Game::addPlayer(const string& name) {
    players.push_back(new Player(name));
}

void Game::setupBoard() {
    // Add snakes
    board.addSnake(99, 10);
    board.addSnake(95, 75);
    board.addSnake(92, 88);
    board.addSnake(89, 68);
    board.addSnake(74, 53);
    board.addSnake(62, 19);
    board.addSnake(46, 25);
    board.addSnake(49, 11);
    
    // Add ladders
    board.addLadder(2, 38);
    board.addLadder(7, 14);
    board.addLadder(8, 31);
    board.addLadder(15, 26);
    board.addLadder(21, 42);
    board.addLadder(28, 84);
    board.addLadder(36, 44);
    board.addLadder(51, 67);
    board.addLadder(71, 91);
    board.addLadder(78, 98);
    
    board.displayInfo();
}

bool Game::makeMove() {
    if (gameOver || players.empty()) return false;
    
    Player* currentPlayer = getCurrentPlayer();
    cout << "\n" << currentPlayer->getName() << "'s turn" << endl;
    
    int roll = dice.roll();
    cout << "Rolled: " << roll << endl;
    
    movePlayer(currentPlayer, roll);
    
    if (checkWin(currentPlayer)) {
        currentPlayer->setWinner(true);
        gameOver = true;
        cout << "\nCongratulations! " << currentPlayer->getName() << " wins!" << endl;
        return false;
    }
    
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    return true;
}

void Game::play() {
    if (players.empty()) {
        cout << "No players in the game!" << endl;
        return;
    }
    
    cout << "\nStarting the game..." << endl;
    while (makeMove()) {
        displayStatus();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Game::displayStatus() const {
    cout << "\nCurrent Game Status:" << endl;
    for (const auto& player : players) {
        cout << player->getName() << " at position " << player->getPosition() << endl;
    }
}

void Game::movePlayer(Player* player, int steps) {
    int newPosition = player->getPosition() + steps;
    
    if (newPosition > board.getSize()) {
        cout << "Cannot move, need exact number to finish" << endl;
        return;
    }
    
    newPosition = board.getNextPosition(newPosition);
    player->setPosition(newPosition);
    
    cout << player->getName() << " moved to position " << newPosition << endl;
}

bool Game::checkWin(Player* player) const {
    return player->getPosition() == board.getSize();
}

Player* Game::getCurrentPlayer() const {
    return players[currentPlayerIndex];
} 

// ===== Player.cpp =====
Player::Player(string name)
    : name(name), position(0), winner(false) {}

string Player::getName() const { return name; }
int Player::getPosition() const { return position; }
bool Player::isWinner() const { return winner; }

void Player::setPosition(int position) {
    this->position = position;
}

void Player::setWinner(bool status) {
    winner = status;
}

void Player::displayInfo() const {
    cout << "Player: " << name << endl;
    cout << "Position: " << position << endl;
    cout << "Status: " << (winner ? "Winner!" : "Playing") << endl;
} 

// ===== GameDemo.cpp =====
int main() {
    Game game;
    
    // Add players
    game.addPlayer("Player 1");
    game.addPlayer("Player 2");
    game.addPlayer("Player 3");
    
    // Setup board with snakes and ladders
    game.setupBoard();
    
    // Start the game
    game.play();
    
    return 0;
} 

