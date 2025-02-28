using System;

namespace TicTacToe
{
    public class Board
    {
        private readonly char[,] _grid;
        private int _movesCount;

        public Board()
        {
            _grid = new char[3, 3];
            InitializeBoard();
        }

        private void InitializeBoard()
        {
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    _grid[row, col] = '-';
                }
            }
            _movesCount = 0;
        }

        public void MakeMove(int row, int col, char symbol)
        {
            if (row < 0 || row >= 3 || col < 0 || col >= 3 || _grid[row, col] != '-')
            {
                throw new ArgumentException("Invalid move!");
            }
            _grid[row, col] = symbol;
            _movesCount++;
        }

        public bool IsFull()
        {
            return _movesCount == 9;
        }

        public bool HasWinner()
        {
            // Check rows
            for (int row = 0; row < 3; row++)
            {
                if (_grid[row, 0] != '-' && _grid[row, 0] == _grid[row, 1] && _grid[row, 1] == _grid[row, 2])
                {
                    return true;
                }
            }

            // Check columns
            for (int col = 0; col < 3; col++)
            {
                if (_grid[0, col] != '-' && _grid[0, col] == _grid[1, col] && _grid[1, col] == _grid[2, col])
                {
                    return true;
                }
            }

            // Check diagonals
            if (_grid[0, 0] != '-' && _grid[0, 0] == _grid[1, 1] && _grid[1, 1] == _grid[2, 2])
            {
                return true;
            }

            return _grid[0, 2] != '-' && _grid[0, 2] == _grid[1, 1] && _grid[1, 1] == _grid[2, 0];
        }

        public void PrintBoard()
        {
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    Console.Write(_grid[row, col] + " ");
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
    }
}