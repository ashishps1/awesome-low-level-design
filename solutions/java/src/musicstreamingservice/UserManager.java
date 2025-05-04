package musicstreamingservice;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class UserManager {
    private static UserManager instance;
    private final Map<String, User> users;

    private UserManager() {
        users = new ConcurrentHashMap<>();
    }

    public static synchronized UserManager getInstance() {
        if (instance == null) {
            instance = new UserManager();
        }
        return instance;
    }

    public void registerUser(User user) {
        users.put(user.getId(), user);
    }

    public Map<String, User> getUsers() {
        return users;
    }

    public User getUser(String userId) {
        return users.get(userId);
    }

    public Playlist getUserPlaylist(String userId, String playlistId) {
        return users.get(userId).getPlaylist(playlistId);
    }
}