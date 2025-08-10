class Artist : Subject
{
    private readonly string id;
    private readonly string name;
    private readonly List<Album> discography = new List<Album>();

    public Artist(string id, string name)
    {
        this.id = id;
        this.name = name;
    }

    public void ReleaseAlbum(Album album)
    {
        discography.Add(album);
        Console.WriteLine($"[System] Artist {name} has released a new album: {album.GetTitle()}");
        NotifyObservers(this, album);
    }

    public string GetId() => id;
    public string GetName() => name;
}