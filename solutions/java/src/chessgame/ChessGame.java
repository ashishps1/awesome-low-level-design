package chessgame;

import chessgame.pieces.Piece;

import java.util.Scanner;

public class ChessGame {
    private final Board board;
    private final Player[] players;
    private int currentPlayer;

    public ChessGame() {
        board = new Board();
        players = new Player[]{new Player(Color.WHITE), new Player(Color.BLACK)};
        currentPlayer = 0;
    }

    public void start() {
        // Game loop
        while (!isGameOver()) {
            Player player = players[currentPlayer];
            System.out.println(player.getColor() + "'s turn.");

            // Get move from the player
            Move move = getPlayerMove(player);

            // Make the move on the board
            try {
                player.makeMove(board, move);
            } catch (InvalidMoveException e) {
                System.out.println(e.getMessage());
                System.out.println("Try again!");
                continue;
            }

            // Switch to the next player
            currentPlayer = (currentPlayer + 1) % 2;
        }

        // Display game result
        displayResult();
    }

    private boolean isGameOver() {
        return board.isCheckmate(players[0].getColor()) || board.isCheckmate(players[1].getColor()) ||
                board.isStalemate(players[0].getColor()) || board.isStalemate(players[1].getColor());
    }

    private Move getPlayerMove(Player player) {
        // TODO: Implement logic to get a valid move from the player
        // For simplicity, let's assume the player enters the move via console input
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter source row: ");
        int sourceRow = scanner.nextInt();
        System.out.print("Enter source column: ");
        int sourceCol = scanner.nextInt();
        System.out.print("Enter destination row: ");
        int destRow = scanner.nextInt();
        System.out.print("Enter destination column: ");
        int destCol = scanner.nextInt();

        Piece piece = board.getPiece(sourceRow, sourceCol);
        if (piece == null || piece.getColor() != player.getColor()) {
            throw new IllegalArgumentException("Invalid piece selection!");
        }

        return new Move(piece, destRow, destCol);
    }

    private void displayResult() {
        if (board.isCheckmate(Color.WHITE)) {
            System.out.println("Black wins by checkmate!");
        } else if (board.isCheckmate(Color.BLACK)) {
            System.out.println("White wins by checkmate!");
        } else if (board.isStalemate(Color.WHITE) || board.isStalemate(Color.BLACK)) {
            System.out.println("The game ends in a stalemate!");
        }
    }
}
