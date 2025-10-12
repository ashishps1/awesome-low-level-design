class PlayerRepository
{
    private readonly Dictionary<string, Player> players = new Dictionary<string, Player>();

    public void Save(Player player)
    {
        players[player.GetId()] = player;
    }

    public Player FindById(string id)
    {
        return players.ContainsKey(id) ? players[id] : null;
    }
}