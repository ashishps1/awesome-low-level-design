# Snake and Ladder Game (LLD)

## Problem Statement

Design and implement a Snake and Ladder Game that allows multiple players to play on a board with snakes and ladders, simulates dice rolls, and determines the winner.

---

## Requirements

- **Multiple Players:** The game supports two or more players.
- **Board:** The game uses a board with a configurable size (typically 1 to 100).
- **Snakes and Ladders:** The board contains snakes (which move players down) and ladders (which move players up).
- **Dice Roll:** Players roll a dice to determine their move.
- **Turn Management:** Players take turns in a round-robin fashion.
- **Win Condition:** The first player to reach the last cell wins.
- **Input Validation:** The game prevents invalid moves (e.g., moving beyond the last cell).
- **Extensibility:** Easy to add new features such as multiple dice, power-ups, or custom board sizes.

---

## Core Entities

- **SnakeAndLadderGame:** Main class that manages the game flow, player turns, and win condition.
- **Board:** Represents the game board, including snakes, ladders, and player positions.
- **Snake:** Represents a snake with a start and end position.
- **Ladder:** Represents a ladder with a start and end position.
- **Player:** Represents a player with a name and current position.
- **Dice:** Simulates dice rolls.

---

## Class Design

### 1. SnakeAndLadderGame
- **Fields:** Board board, List<Player> players, Dice dice, boolean isGameOver
- **Methods:** start(), playTurn(), movePlayer(Player, int steps), checkWin(Player), getCurrentPlayer()

### 2. Board
- **Fields:** int size, List<Snake> snakes, List<Ladder> ladders, Map<Player, Integer> playerPositions
- **Methods:** getNextPosition(int current, int roll), addSnake(Snake), addLadder(Ladder), setPlayerPosition(Player, int position), getPlayerPosition(Player)

### 3. Snake
- **Fields:** int start, int end

### 4. Ladder
- **Fields:** int start, int end

### 5. Player
- **Fields:** String name, int position

### 6. Dice
- **Methods:** roll()

---

## Example Usage

```java
List<Player> players = List.of(new Player("Alice"), new Player("Bob"));
List<Snake> snakes = List.of(new Snake(14, 7), new Snake(31, 26));
List<Ladder> ladders = List.of(new Ladder(3, 22), new Ladder(5, 8));
Board board = new Board(100, snakes, ladders, players);
Dice dice = new Dice();

SnakeAndLadderGame game = new SnakeAndLadderGame(board, players, dice);
game.start();
```

---

## Demo

See `SnakeAndLadderDemo.java` for a sample usage and simulation of the snake and ladder game.

---

## Extending the Framework

- **Add multiple dice:** Allow rolling more than one dice per turn.
- **Add power-ups:** Introduce special cells with unique effects.
- **Add custom board sizes:** Support boards larger or smaller than 100 cells.

---