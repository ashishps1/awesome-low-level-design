namespace SnakeAndLadderGame
{
    public class Player
    {
        public string Name { get; }
        public int Position { get; private set; }

        public Player(string name)
        {
            Name = name;
            Position = 0;
        }

        public void SetPosition(int position)
        {
            Position = position;
        }
    }
}