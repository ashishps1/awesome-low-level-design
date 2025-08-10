class Movie : MovieSubject
{
    private readonly string id;
    private readonly string title;
    private readonly int durationInMinutes;

    public Movie(string id, string title, int durationInMinutes)
    {
        this.id = id;
        this.title = title;
        this.durationInMinutes = durationInMinutes;
    }

    public string GetId() { return id; }
    public string GetTitle() { return title; }
}