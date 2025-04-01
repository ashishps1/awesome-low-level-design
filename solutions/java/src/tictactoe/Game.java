package tictactoe;

import java.util.Scanner;

public class Game {
    private final Player player1;
    private final Player player2;
    private final Board board;
    private Player currentPlayer;

    public Game(Player player1, Player player2) {
        this.player1 = player1;
        this.player2 = player2;
        this.board = new Board();
        this.currentPlayer = player1;
    }

    public void play() {
        board.printBoard();

        while (!board.isFull() && !board.hasWinner()) {
            System.out.println(currentPlayer.getName() + "'s turn.");
            int row = getValidInput("Enter row (0-2): ");
            int col = getValidInput("Enter column (0-2): ");

            try {
                board.makeMove(row, col, currentPlayer.getSymbol());
                board.printBoard();
                switchPlayer();
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }

        if (board.hasWinner()) {
            switchPlayer();
            System.out.println(currentPlayer.getName() + " wins!");
        } else {
            System.out.println("It's a draw!");
        }
    }

    private void switchPlayer() {
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }

    private int getValidInput(String message) {
        Scanner scanner = new Scanner(System.in);
        int input;

        while (true) {
            System.out.print(message);
            if (scanner.hasNextInt()) {
                input = scanner.nextInt();
                if (input >= 0 && input <= 2) {
                    return input;
                }
            } else {
                scanner.next();
            }
            System.out.println("Invalid input! Please enter a number between 0 and 2.");
        }
    }
}
