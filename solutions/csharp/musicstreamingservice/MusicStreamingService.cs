namespace MusicStreamingService
{
    public class MusicStreamingService
    {
        public MusicLibrary MusicLibrary { get; }
        public UserManager UserManager { get; }
        public MusicRecommender MusicRecommender { get; }

        public MusicStreamingService()
        {
            MusicLibrary = MusicLibrary.GetInstance();
            UserManager = UserManager.GetInstance();
            MusicRecommender = MusicRecommender.GetInstance();
        }

        public void Start()
        {
            // Starting logic
        }
    }
}