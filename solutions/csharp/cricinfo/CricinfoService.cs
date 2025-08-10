class CricInfoService
{
    private static volatile CricInfoService instance;
    private static readonly object lockObject = new object();
    private readonly MatchRepository matchRepository;
    private readonly PlayerRepository playerRepository;

    private CricInfoService()
    {
        matchRepository = new MatchRepository();
        playerRepository = new PlayerRepository();
    }

    public static CricInfoService GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new CricInfoService();
                }
            }
        }
        return instance;
    }

    public Match CreateMatch(Team team1, Team team2, IMatchFormatStrategy format)
    {
        string matchId = Guid.NewGuid().ToString();
        var match = new Match(matchId, team1, team2, format);
        matchRepository.Save(match);
        Console.WriteLine($"Match {format.GetFormatName()} created between {team1.GetName()} and {team2.GetName()}.");
        return match;
    }

    public void StartMatch(string matchId)
    {
        var match = matchRepository.FindById(matchId);
        if (match != null)
        {
            match.SetState(new LiveState());
            Console.WriteLine($"Match {matchId} is now LIVE.");
        }
    }

    public void ProcessBallUpdate(string matchId, Ball ball)
    {
        var match = matchRepository.FindById(matchId);
        match?.ProcessBall(ball);
    }

    public void StartNextInnings(string matchId)
    {
        var match = matchRepository.FindById(matchId);
        match?.StartNextInnings();
    }

    public void SubscribeToMatch(string matchId, IMatchObserver observer)
    {
        var match = matchRepository.FindById(matchId);
        match?.AddObserver(observer);
    }

    public void EndMatch(string matchId)
    {
        var match = matchRepository.FindById(matchId);
        if (match != null)
        {
            match.SetState(new FinishedState());
            Console.WriteLine($"Match {matchId} has FINISHED.");
        }
    }

    public Player AddPlayer(string playerId, string playerName, PlayerRole playerRole)
    {
        var player = new Player(playerId, playerName, playerRole);
        playerRepository.Save(player);
        return player;
    }
}