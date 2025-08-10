class Song : IPlayable
{
    private readonly string id;
    private readonly string title;
    private readonly Artist artist;
    private readonly int durationInSeconds;

    public Song(string id, string title, Artist artist, int durationInSeconds)
    {
        this.id = id;
        this.title = title;
        this.artist = artist;
        this.durationInSeconds = durationInSeconds;
    }

    public List<Song> GetTracks()
    {
        return new List<Song> { this };
    }

    public override string ToString()
    {
        return $"'{title}' by {artist.GetName()}";
    }

    public string GetId() => id;
    public string GetTitle() => title;
    public Artist GetArtist() => artist;
}