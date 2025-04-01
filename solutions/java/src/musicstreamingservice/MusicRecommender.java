package musicstreamingservice;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class MusicRecommender {
    private static MusicRecommender instance;
    private final Map<String, List<Song>> userRecommendations;

    private MusicRecommender() {
        userRecommendations = new ConcurrentHashMap<>();
    }

    public static synchronized MusicRecommender getInstance() {
        if (instance == null) {
            instance = new MusicRecommender();
        }
        return instance;
    }

    public List<Song> recommendSongs(User user) {
        // Generate song recommendations based on user's listening history and preferences
        // ...
        return userRecommendations.getOrDefault(user.getId(), new ArrayList<>());
    }
}
