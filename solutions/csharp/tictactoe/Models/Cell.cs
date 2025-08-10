class Cell
{
    private Symbol symbol;

    public Cell()
    {
        symbol = Symbol.EMPTY;
    }

    public Symbol GetSymbol() { return symbol; }
    public void SetSymbol(Symbol symbol) { this.symbol = symbol; }

    public char GetSymbolChar()
    {
        switch (symbol)
        {
            case Symbol.X: return 'X';
            case Symbol.O: return 'O';
            case Symbol.EMPTY: return '_';
            default: return '_';
        }
    }
}