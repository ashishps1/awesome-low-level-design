class Show
{
    private readonly string id;
    private readonly Movie movie;
    private readonly Screen screen;
    private readonly DateTime startTime;
    private readonly IPricingStrategy pricingStrategy;

    public Show(string id, Movie movie, Screen screen, DateTime startTime, IPricingStrategy pricingStrategy)
    {
        this.id = id;
        this.movie = movie;
        this.screen = screen;
        this.startTime = startTime;
        this.pricingStrategy = pricingStrategy;
    }

    public string GetId() { return id; }
    public Movie GetMovie() { return movie; }
    public Screen GetScreen() { return screen; }
    public DateTime GetStartTime() { return startTime; }
    public IPricingStrategy GetPricingStrategy() { return pricingStrategy; }
}