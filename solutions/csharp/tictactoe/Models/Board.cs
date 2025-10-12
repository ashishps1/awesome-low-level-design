using System;


class Board
{
    private readonly int size;
    private int movesCount;
    private readonly Cell[,] board;

    public Board(int size)
    {
        this.size = size;
        this.board = new Cell[size, size];
        movesCount = 0;
        InitializeBoard();
    }

    private void InitializeBoard()
    {
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                board[row, col] = new Cell();
            }
        }
    }

    public bool PlaceSymbol(int row, int col, Symbol symbol)
    {
        if (row < 0 || row >= size || col < 0 || col >= size)
        {
            throw new InvalidMoveException("Invalid position: out of bounds.");
        }
        if (board[row, col].GetSymbol() != Symbol.EMPTY)
        {
            throw new InvalidMoveException("Invalid position: cell is already occupied.");
        }

        board[row, col].SetSymbol(symbol);
        movesCount++;
        return true;
    }

    public Cell GetCell(int row, int col)
    {
        if (row < 0 || row >= size || col < 0 || col >= size)
        {
            return null;
        }
        return board[row, col];
    }

    public bool IsFull() { return movesCount == size * size; }

    public void PrintBoard()
    {
        Console.WriteLine("-------------");
        for (int i = 0; i < size; i++)
        {
            Console.Write("| ");
            for (int j = 0; j < size; j++)
            {
                Console.Write(board[i, j].GetSymbolChar() + " | ");
            }
            Console.WriteLine();
            Console.WriteLine("-------------");
        }
    }

    public int GetSize() => size;
}