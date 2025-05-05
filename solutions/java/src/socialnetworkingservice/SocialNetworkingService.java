package socialnetworkingservice;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class SocialNetworkingService {
    private static SocialNetworkingService instance;
    private final Map<String, User> usersMap;
    private final Map<String, Post> postsMap;

    private SocialNetworkingService() {
        usersMap = new ConcurrentHashMap<>();
        postsMap = new ConcurrentHashMap<>();
    }

    public static synchronized SocialNetworkingService getInstance() {
        if (instance == null) {
            instance = new SocialNetworkingService();
        }
        return instance;
    }

    public User registerUser(String name, String email, String password, String bio) {
        User user = new User(name, email, password, bio);
        usersMap.put(user.getId(), user);
        return user;
    }

    public User loginUser(String email, String password) {
        for (User user : usersMap.values()) {
            if (user.getEmail().equals(email) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }

    public void sendFriendRequest(String fromId, String toId) {
        User from = usersMap.get(fromId);
        User to = usersMap.get(toId);

        if (from == null || to == null) throw new IllegalArgumentException("User not found");
        if (from.isFriend(to)) return;

        FriendRequest req = new FriendRequest(from, to);
        to.receiveRequest(req);
        sendNotification(to, NotificationType.FRIEND_REQUEST_ACCEPTED, "Friend request from: " + from.getName());
    }

    public void acceptFriendRequest(String toId, String fromId) {
        User to = usersMap.get(toId);
        User from = usersMap.get(fromId);

        FriendRequest req = to.getRequestFrom(from);
        if (req == null) throw new IllegalArgumentException("No pending request");

        req.accept();
        to.addFriend(from);
        from.addFriend(to);
        sendNotification(from, NotificationType.FRIEND_REQUEST_ACCEPTED, "You are now friends with: " + to.getName());
    }

    public Post createPost(String userId, String content) {
        User user = usersMap.get(userId);
        Post post = new Post(user, content);
        user.addPost(post);
        postsMap.put(post.getId(), post);
        return post;
    }

    public void likePost(String userId, String postId) {
        User user = usersMap.get(userId);
        Post post = postsMap.get(postId);
        post.like(user);
        sendNotification(post.getAuthor(), NotificationType.LIKE, "Your post was liked by " + user.getName());
    }

    public void commentOnPost(String userId, String postId, String text) {
        User user = usersMap.get(userId);
        Post post = postsMap.get(postId);
        post.comment(user, text);
        sendNotification(post.getAuthor(), NotificationType.COMMENT, "Your post received a comment from " + user.getName());
    }

    public List<Post> getNewsFeed(String userId) {
        User user = usersMap.get(userId);
        return user.getFriends().stream()
                .flatMap(friend -> friend.getPosts().stream())
                .sorted(Comparator.comparing(Post::getTimestamp).reversed())
                .limit(20)
                .toList();
    }

    private void sendNotification(User receiver, NotificationType type, String notificationText) {
        Notification notification = new Notification(receiver, type, notificationText);
        receiver.addNotification(notification);
    }

    public List<Notification> getNotifications(String userId) {
        return usersMap.get(userId).getNotifications();
    }
}
