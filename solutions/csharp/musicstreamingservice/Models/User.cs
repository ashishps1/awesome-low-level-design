class User : IArtistObserver
{
    private readonly string id;
    private readonly string name;
    private readonly PlaybackStrategy playbackStrategy;
    private readonly HashSet<Artist> followedArtists = new HashSet<Artist>();

    public User(string id, string name, PlaybackStrategy strategy)
    {
        this.id = id;
        this.name = name;
        this.playbackStrategy = strategy;
    }

    public void FollowArtist(Artist artist)
    {
        followedArtists.Add(artist);
        artist.AddObserver(this);
    }

    public void Update(Artist artist, Album newAlbum)
    {
        Console.WriteLine($"[Notification for {name}] Your followed artist {artist.GetName()} " +
                         $"just released a new album: {newAlbum.GetTitle()}!");
    }

    public PlaybackStrategy GetPlaybackStrategy() => playbackStrategy;
    public string GetId() => id;
    public string GetName() => name;
}

class UserBuilder
{
    private readonly string id;
    private readonly string name;
    private PlaybackStrategy playbackStrategy;

    public UserBuilder(string name)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
    }

    public UserBuilder WithSubscription(SubscriptionTier tier, int songsPlayed)
    {
        this.playbackStrategy = PlaybackStrategy.GetStrategy(tier, songsPlayed);
        return this;
    }

    public User Build()
    {
        return new User(id, name, playbackStrategy);
    }
}