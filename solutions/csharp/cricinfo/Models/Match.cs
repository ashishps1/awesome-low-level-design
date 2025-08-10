class Match
{
    private readonly string id;
    private readonly Team team1;
    private readonly Team team2;
    private readonly IMatchFormatStrategy formatStrategy;
    private readonly List<Innings> innings;
    private IMatchState currentState;
    private MatchStatus currentStatus;
    private readonly List<IMatchObserver> observers;
    private Team winner;
    private string resultMessage;

    public Match(string matchId, Team t1, Team t2, IMatchFormatStrategy format)
    {
        id = matchId;
        team1 = t1;
        team2 = t2;
        formatStrategy = format;
        innings = new List<Innings> { new Innings(team1, team2) };
        currentState = new ScheduledState();
        observers = new List<IMatchObserver>();
        resultMessage = "";
    }

    public void ProcessBall(Ball ball)
    {
        currentState.ProcessBall(this, ball);
    }

    public void StartNextInnings()
    {
        currentState.StartNextInnings(this);
    }

    public void CreateNewInnings()
    {
        if (innings.Count >= formatStrategy.GetTotalInnings())
        {
            Console.WriteLine("Cannot create a new innings, match has already reached its limit.");
            return;
        }

        var nextInnings = new Innings(team2, team1);
        innings.Add(nextInnings);
    }

    public void AddObserver(IMatchObserver observer)
    {
        observers.Add(observer);
    }

    public void RemoveObserver(IMatchObserver observer)
    {
        observers.Remove(observer);
    }

    public void NotifyObservers(Ball ball)
    {
        foreach (var observer in observers)
        {
            observer.Update(this, ball);
        }
    }

    public Innings GetCurrentInnings()
    {
        return innings.Last();
    }

    public string GetId() => id;
    public Team GetTeam1() => team1;
    public Team GetTeam2() => team2;
    public IMatchFormatStrategy GetFormatStrategy() => formatStrategy;
    public List<Innings> GetInnings() => innings;
    public MatchStatus GetCurrentStatus() => currentStatus;
    public Team GetWinner() => winner;
    public string GetResultMessage() => resultMessage;

    public void SetState(IMatchState state) { currentState = state; }
    public void SetCurrentStatus(MatchStatus status) { currentStatus = status; }
    public void SetWinner(Team w) { winner = w; }
    public void SetResultMessage(string message) { resultMessage = message; }
}