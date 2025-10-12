class Player
{
    private readonly string id;
    private readonly string name;
    private readonly PlayerRole role;
    private readonly PlayerStats stats;

    public Player(string playerId, string playerName, PlayerRole playerRole)
    {
        id = playerId;
        name = playerName;
        role = playerRole;
        stats = new PlayerStats();
    }

    public string GetId() => id;
    public string GetName() => name;
    public PlayerRole GetRole() => role;
    public PlayerStats GetStats() => stats;
}