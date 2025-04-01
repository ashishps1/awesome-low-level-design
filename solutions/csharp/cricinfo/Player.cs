namespace Cricinfo
{
    public class Player
    {
        private readonly string id;
        private readonly string name;
        private readonly string role;

        public Player(string id, string name, string role)
        {
            this.id = id;
            this.name = name;
            this.role = role;
        }
    }
}