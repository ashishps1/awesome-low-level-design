package tictactoe.enums;

public enum Symbol {
    X('X'),
    O('O'),
    EMPTY('_');

    private final char symbol;

    Symbol(char symbol) {
        this.symbol = symbol;
    }

    public char getChar() {
        return symbol;
    }
}
