class Player
{
    private PlayerState state;
    private PlayerStatus status;
    private List<Song> queue = new List<Song>();
    private int currentIndex = -1;
    private Song currentSong;
    private User currentUser;

    public Player()
    {
        this.state = new StoppedState();
        this.status = PlayerStatus.STOPPED;
    }

    public void Load(IPlayable playable, User user)
    {
        this.currentUser = user;
        this.queue = playable.GetTracks();
        this.currentIndex = 0;
        Console.WriteLine($"Loaded {queue.Count} tracks for user {user.GetName()}.");
        this.state = new StoppedState();
    }

    public void PlayCurrentSongInQueue()
    {
        if (currentIndex >= 0 && currentIndex < queue.Count)
        {
            Song songToPlay = queue[currentIndex];
            currentUser.GetPlaybackStrategy().Play(songToPlay, this);
        }
    }

    public void ClickPlay() => state.Play(this);
    public void ClickPause() => state.Pause(this);

    public void ClickNext()
    {
        if (currentIndex < queue.Count - 1)
        {
            currentIndex++;
            PlayCurrentSongInQueue();
        }
        else
        {
            Console.WriteLine("End of queue.");
            state.Stop(this);
        }
    }

    public void ChangeState(PlayerState state) => this.state = state;
    public void SetStatus(PlayerStatus status) => this.status = status;
    public void SetCurrentSong(Song song) => this.currentSong = song;
    public bool HasQueue() => queue.Count > 0;
}