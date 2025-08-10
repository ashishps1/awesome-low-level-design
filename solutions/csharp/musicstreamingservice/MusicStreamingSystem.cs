class MusicStreamingSystem
{
    private static MusicStreamingSystem instance;
    private static readonly object lockObject = new object();
    private readonly Dictionary<string, User> users = new Dictionary<string, User>();
    private readonly Dictionary<string, Song> songs = new Dictionary<string, Song>();
    private readonly Dictionary<string, Artist> artists = new Dictionary<string, Artist>();
    private readonly Player player;
    private readonly SearchService searchService;
    private readonly RecommendationService recommendationService;

    private MusicStreamingSystem()
    {
        this.player = new Player();
        this.searchService = new SearchService();
        this.recommendationService = new RecommendationService(new GenreBasedRecommendationStrategy());
    }

    public static MusicStreamingSystem GetInstance()
    {
        if (instance == null)
        {
            lock (lockObject)
            {
                if (instance == null)
                {
                    instance = new MusicStreamingSystem();
                }
            }
        }
        return instance;
    }

    public void RegisterUser(User user)
    {
        users[user.GetId()] = user;
    }

    public Song AddSong(string id, string title, string artistId, int duration)
    {
        Song song = new Song(id, title, artists[artistId], duration);
        songs[song.GetId()] = song;
        return song;
    }

    public void AddArtist(Artist artist)
    {
        artists[artist.GetId()] = artist;
    }

    public List<Song> SearchSongsByTitle(string title)
    {
        return searchService.SearchSongsByTitle(songs.Values.ToList(), title);
    }

    public List<Song> GetSongRecommendations()
    {
        return recommendationService.GenerateRecommendations(songs.Values.ToList());
    }

    public Player GetPlayer() => player;
}