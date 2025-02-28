using System;
using System.Collections.Generic;

namespace SnakeAndLadderGame
{
    public class SnakeAndLadderGame
    {
        private readonly Board _board;
        private readonly List<Player> _players;
        private readonly Dice _dice;
        private int _currentPlayerIndex;

        public SnakeAndLadderGame(List<string> playerNames)
        {
            _board = new Board();
            _dice = new Dice();
            _players = new List<Player>();
            foreach (var playerName in playerNames)
            {
                _players.Add(new Player(playerName));
            }
            _currentPlayerIndex = 0;
        }

        public void Play()
        {
            while (!IsGameOver())
            {
                Player currentPlayer = _players[_currentPlayerIndex];
                int diceRoll = _dice.Roll();
                int newPosition = currentPlayer.Position + diceRoll;

                if (newPosition <= _board.GetBoardSize())
                {
                    currentPlayer.SetPosition(_board.GetNewPositionAfterSnakeOrLadder(newPosition));
                    Console.WriteLine($"{currentPlayer.Name} rolled a {diceRoll} and moved to position {currentPlayer.Position}");
                }

                if (currentPlayer.Position == _board.GetBoardSize())
                {
                    Console.WriteLine($"{currentPlayer.Name} wins!");
                    break;
                }

                _currentPlayerIndex = (_currentPlayerIndex + 1) % _players.Count;
            }
        }

        private bool IsGameOver()
        {
            foreach (var player in _players)
            {
                if (player.Position == _board.GetBoardSize())
                {
                    return true;
                }
            }
            return false;
        }
    }
}