# Chess Game (LLD)

## Problem Statement

Design and implement a Chess Game that allows two players to play chess on a standard 8x8 board, enforces chess rules, validates moves, and determines game status (check, checkmate, stalemate).

---

## Requirements

- **Two Players:** The game is played between two players (White and Black).
- **Board:** The game uses a standard 8x8 chess board.
- **Pieces:** All standard chess pieces (King, Queen, Rook, Bishop, Knight, Pawn) with their movement rules.
- **Move Validation:** The game validates moves according to chess rules and prevents illegal moves.
- **Turn Management:** Players alternate turns.
- **Game Status:** The game detects check, checkmate, and stalemate.
- **Exception Handling:** The system throws exceptions for invalid moves.
- **Extensibility:** Easy to add features such as move history, undo, or AI opponent.

---

## Core Entities

- **ChessGame:** Main class that manages the game flow, player turns, and game status.
- **Board:** Represents the 8x8 chess board and manages piece positions.
- **Cell:** Represents a cell on the board, with row, column, and piece.
- **Player:** Represents a player with a name and color.
- **Color (enum):** WHITE, BLACK.
- **Move:** Represents a move from one cell to another.
- **Piece (abstract, in pieces/):** Base class for all chess pieces.
- **King, Queen, Rook, Bishop, Knight, Pawn (in pieces/):** Concrete piece classes with movement logic.
- **InvalidMoveException:** Exception thrown for invalid moves.

---

## Class Design

### 1. ChessGame
- **Fields:** Board board, Player[] players, int currentPlayerIndex, boolean isGameOver
- **Methods:** start(), makeMove(Move), switchPlayer(), isCheck(), isCheckmate(), isStalemate(), getCurrentPlayer()

### 2. Board
- **Fields:** Cell[][] grid, List<Piece> pieces
- **Methods:** getCell(int row, int col), movePiece(Move), isCellOccupied(int row, int col), isCheck(Color), isCheckmate(Color), isStalemate(Color), printBoard()

### 3. Cell
- **Fields:** int row, int col, Piece piece
- **Methods:** getPiece(), setPiece(Piece), isEmpty()

### 4. Player
- **Fields:** String name, Color color

### 5. Color (enum)
- Values: WHITE, BLACK

### 6. Move
- **Fields:** Cell from, Cell to

### 7. Piece (abstract, in pieces/)
- **Fields:** Color color, Cell position
- **Methods:** isValidMove(Board, Move), getPossibleMoves(Board)

### 8. InvalidMoveException
- **Thrown:** When a move is not valid according to chess rules

---

## Example Usage

```java
Player white = new Player("Alice", Color.WHITE);
Player black = new Player("Bob", Color.BLACK);
ChessGame game = new ChessGame(white, black);
game.start();

Move move = new Move(game.getBoard().getCell(6, 4), game.getBoard().getCell(4, 4)); // e2 to e4
game.makeMove(move);
```

---

## Demo

See `ChessGameDemo.java` for a sample usage and simulation of the chess game.

---

## Extending the Framework

- **Add move history:** Track all moves for undo/redo or replay.
- **Add AI opponent:** Implement a computer player.
- **Add GUI:** Build a graphical interface for the game.

---