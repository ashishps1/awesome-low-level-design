class Cinema
{
    private readonly string id;
    private readonly string name;
    private readonly City city;
    private readonly List<Screen> screens;

    public Cinema(string id, string name, City city, List<Screen> screens)
    {
        this.id = id;
        this.name = name;
        this.city = city;
        this.screens = screens;
    }

    public string GetId() { return id; }
    public string GetName() { return name; }
    public City GetCity() { return city; }
    public List<Screen> GetScreens() { return screens; }
}