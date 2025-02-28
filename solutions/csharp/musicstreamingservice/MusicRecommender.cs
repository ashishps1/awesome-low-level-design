using System.Collections.Generic;
using System.Collections.Concurrent;

namespace MusicStreamingService
{
    public class MusicRecommender
    {
        private static MusicRecommender instance;
        private readonly ConcurrentDictionary<string, List<Song>> userRecommendations;

        private MusicRecommender()
        {
            userRecommendations = new ConcurrentDictionary<string, List<Song>>();
        }

        public static MusicRecommender GetInstance()
        {
            if (instance == null)
            {
                instance = new MusicRecommender();
            }
            return instance;
        }

        public List<Song> RecommendSongs(User user)
        {
            // Recommendation logic here
            return userRecommendations.TryGetValue(user.Id, out var songs) ? songs : new List<Song>();
        }
    }
}