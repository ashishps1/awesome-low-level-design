class Team
{
    private readonly string id;
    private readonly string name;
    private readonly List<Player> players;

    public Team(string teamId, string teamName, List<Player> teamPlayers)
    {
        id = teamId;
        name = teamName;
        players = teamPlayers;
    }

    public string GetId() => id;
    public string GetName() => name;
    public List<Player> GetPlayers() => players;
}