using System;

namespace ChessGame
{
    public class ChessGame
    {
        private readonly Board board;
        private readonly Player[] players;
        private int currentPlayer;

        public ChessGame()
        {
            board = new Board();
            players = new Player[] { new Player(Color.White), new Player(Color.Black) };
            currentPlayer = 0;
        }

        public void Start()
        {
            // Game loop
            while (!IsGameOver())
            {
                Player player = players[currentPlayer];
                Console.WriteLine($"{player.Color}'s turn.");

                // Get move from the player
                Move move = GetPlayerMove(player);

                // Make the move on the board
                try
                {
                    player.MakeMove(board, move);
                }
                catch (InvalidMoveException e)
                {
                    Console.WriteLine(e.Message);
                    Console.WriteLine("Try again!");
                    continue;
                }

                // Switch to the next player
                currentPlayer = (currentPlayer + 1) % 2;
            }

            // Display game result
            DisplayResult();
        }

        private bool IsGameOver()
        {
            return board.IsCheckmate(players[0].Color) || board.IsCheckmate(players[1].Color) ||
                   board.IsStalemate(players[0].Color) || board.IsStalemate(players[1].Color);
        }

        private Move GetPlayerMove(Player player)
        {
            // TODO: Implement logic to get a valid move from the player
            Console.Write("Enter source row: ");
            int sourceRow = int.Parse(Console.ReadLine());
            Console.Write("Enter source column: ");
            int sourceCol = int.Parse(Console.ReadLine());
            Console.Write("Enter destination row: ");
            int destRow = int.Parse(Console.ReadLine());
            Console.Write("Enter destination column: ");
            int destCol = int.Parse(Console.ReadLine());

            Piece piece = board.GetPiece(sourceRow, sourceCol);
            if (piece == null || piece.Color != player.Color)
            {
                throw new ArgumentException("Invalid piece selection!");
            }

            return new Move(piece, destRow, destCol);
        }

        private void DisplayResult()
        {
            if (board.IsCheckmate(Color.White))
            {
                Console.WriteLine("Black wins by checkmate!");
            }
            else if (board.IsCheckmate(Color.Black))
            {
                Console.WriteLine("White wins by checkmate!");
            }
            else if (board.IsStalemate(Color.White) || board.IsStalemate(Color.Black))
            {
                Console.WriteLine("The game ends in a stalemate!");
            }
        }
    }
}