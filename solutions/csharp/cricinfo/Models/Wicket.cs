class Wicket
{
    private readonly WicketType wicketType;
    private readonly Player playerOut;
    private readonly Player caughtBy;
    private readonly Player runoutBy;

    public Wicket(WicketBuilder builder)
    {
        wicketType = builder.WicketType;
        playerOut = builder.PlayerOut;
        caughtBy = builder.CaughtBy;
        runoutBy = builder.RunoutBy;
    }

    public WicketType GetWicketType() => wicketType;
    public Player GetPlayerOut() => playerOut;
    public Player GetCaughtBy() => caughtBy;
    public Player GetRunoutBy() => runoutBy;
}

class WicketBuilder
{
    private readonly WicketType wicketType;
    private readonly Player playerOut;
    private Player caughtBy;
    private Player runoutBy;

    public WicketBuilder(WicketType type, Player player)
    {
        wicketType = type;
        playerOut = player;
    }

    public WicketBuilder WithCaughtBy(Player player)
    {
        caughtBy = player;
        return this;
    }

    public WicketBuilder WithRunoutBy(Player player)
    {
        runoutBy = player;
        return this;
    }

    public Wicket Build()
    {
        return new Wicket(this);
    }

    internal WicketType WicketType => wicketType;
    internal Player PlayerOut => playerOut;
    internal Player CaughtBy => caughtBy;
    internal Player RunoutBy => runoutBy;
}