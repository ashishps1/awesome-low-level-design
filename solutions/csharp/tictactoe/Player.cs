namespace TicTacToe
{
    public class Player
    {
        public string Name { get; }
        public char Symbol { get; }

        public Player(string name, char symbol)
        {
            Name = name;
            Symbol = symbol;
        }
    }
}