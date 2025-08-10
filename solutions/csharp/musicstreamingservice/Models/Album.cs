class Album : IPlayable
{
    private readonly string title;
    private readonly List<Song> tracks = new List<Song>();

    public Album(string title)
    {
        this.title = title;
    }

    public void AddTrack(Song song)
    {
        tracks.Add(song);
    }

    public List<Song> GetTracks()
    {
        return new List<Song>(tracks);
    }

    public string GetTitle() => title;
}