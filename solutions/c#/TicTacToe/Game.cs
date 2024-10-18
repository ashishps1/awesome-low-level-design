using System;

namespace TicTacToe
{
    public class Game
    {
        private readonly Player _player1;
        private readonly Player _player2;
        private readonly Board _board;
        private Player _currentPlayer;

        public Game(Player player1, Player player2)
        {
            _player1 = player1;
            _player2 = player2;
            _board = new Board();
            _currentPlayer = player1;
        }

        public void Play()
        {
            _board.PrintBoard();

            while (!_board.IsFull() && !_board.HasWinner())
            {
                Console.WriteLine($"{_currentPlayer.Name}'s turn.");
                int row = GetValidInput("Enter row (0-2): ");
                int col = GetValidInput("Enter column (0-2): ");

                try
                {
                    _board.MakeMove(row, col, _currentPlayer.Symbol);
                    _board.PrintBoard();
                    SwitchPlayer();
                }
                catch (ArgumentException e)
                {
                    Console.WriteLine(e.Message);
                }
            }

            if (_board.HasWinner())
            {
                SwitchPlayer();
                Console.WriteLine($"{_currentPlayer.Name} wins!");
            }
            else
            {
                Console.WriteLine("It's a draw!");
            }
        }

        private void SwitchPlayer()
        {
            _currentPlayer = (_currentPlayer == _player1) ? _player2 : _player1;
        }

        private int GetValidInput(string message)
        {
            int input;
            while (true)
            {
                Console.Write(message);
                if (int.TryParse(Console.ReadLine(), out input) && input >= 0 && input <= 2)
                {
                    return input;
                }
                Console.WriteLine("Invalid input! Please enter a number between 0 and 2.");
            }
        }
    }
}