class Player
{
    private readonly string name;
    private readonly Symbol symbol;

    public Player(string name, Symbol symbol)
    {
        this.name = name;
        this.symbol = symbol;
    }

    public string GetName() { return name; }
    public Symbol GetSymbol() { return symbol; }

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