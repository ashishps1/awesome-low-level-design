class Ball
{
    private readonly int ballNumber;
    private readonly Player bowledBy;
    private readonly Player facedBy;
    private readonly int runsScored;
    private readonly Wicket wicket;
    private readonly ExtraType? extraType;
    private readonly string commentary;

    public Ball(BallBuilder builder)
    {
        ballNumber = builder.BallNumber;
        bowledBy = builder.BowledBy;
        facedBy = builder.FacedBy;
        runsScored = builder.RunsScored;
        wicket = builder.Wicket;
        extraType = builder.ExtraType;
        commentary = builder.Commentary;
    }

    public bool IsWicket() => wicket != null;
    public bool IsBoundary() => runsScored == 4 || runsScored == 6;

    public int GetBallNumber() => ballNumber;
    public Player GetBowledBy() => bowledBy;
    public Player GetFacedBy() => facedBy;
    public int GetRunsScored() => runsScored;
    public Wicket GetWicket() => wicket;
    public ExtraType? GetExtraType() => extraType;
    public string GetCommentary() => commentary;
}

class BallBuilder
{
    private int ballNumber;
    private Player bowledBy;
    private Player facedBy;
    private int runsScored;
    private Wicket wicket;
    private ExtraType? extraType;
    private string commentary;

    public BallBuilder WithBallNumber(int number)
    {
        ballNumber = number;
        return this;
    }

    public BallBuilder WithBowledBy(Player bowler)
    {
        bowledBy = bowler;
        return this;
    }

    public BallBuilder WithFacedBy(Player batsman)
    {
        facedBy = batsman;
        return this;
    }

    public BallBuilder WithRuns(int runs)
    {
        runsScored = runs;
        return this;
    }

    public BallBuilder WithWicket(Wicket w)
    {
        wicket = w;
        return this;
    }

    public BallBuilder WithExtraType(ExtraType extra)
    {
        extraType = extra;
        return this;
    }

    public BallBuilder WithCommentary(string comm)
    {
        commentary = comm;
        return this;
    }

    public Ball Build()
    {
        var tempBall = new Ball(this);

        if (string.IsNullOrEmpty(commentary))
        {
            commentary = CommentaryManager.GetInstance().GenerateCommentary(tempBall);
        }

        return new Ball(this);
    }

    internal int BallNumber => ballNumber;
    internal Player BowledBy => bowledBy;
    internal Player FacedBy => facedBy;
    internal int RunsScored => runsScored;
    internal Wicket Wicket => wicket;
    internal ExtraType? ExtraType => extraType;
    internal string Commentary => commentary;
}