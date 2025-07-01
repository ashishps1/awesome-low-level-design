package chessgame;

public class ChessGameDemo {
    public static void run() {
        ChessGame chessGame = new ChessGame();
        chessGame.setPlayers("Alice", "Bob");
        chessGame.start();
    }
}
