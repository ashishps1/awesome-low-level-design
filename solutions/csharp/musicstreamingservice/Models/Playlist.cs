class Playlist : IPlayable
{
    private readonly string name;
    private readonly List<Song> tracks = new List<Song>();

    public Playlist(string name)
    {
        this.name = name;
    }

    public void AddTrack(Song song)
    {
        tracks.Add(song);
    }

    public List<Song> GetTracks()
    {
        return new List<Song>(tracks);
    }
}