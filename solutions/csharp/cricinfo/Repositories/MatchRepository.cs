class MatchRepository
{
    private readonly Dictionary<string, Match> matches = new Dictionary<string, Match>();

    public void Save(Match match)
    {
        matches[match.GetId()] = match;
    }

    public Match FindById(string id)
    {
        return matches.ContainsKey(id) ? matches[id] : null;
    }
}