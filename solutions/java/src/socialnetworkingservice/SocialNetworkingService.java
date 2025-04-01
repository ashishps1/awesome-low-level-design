package socialnetworkingservice;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;

public class SocialNetworkingService {
    private static SocialNetworkingService instance;
    private final Map<String, User> users;
    private final Map<String, Post> posts;
    private final Map<String, List<Notification>> notifications;

    private SocialNetworkingService() {
        users = new ConcurrentHashMap<>();
        posts = new ConcurrentHashMap<>();
        notifications = new ConcurrentHashMap<>();
    }

    public static synchronized SocialNetworkingService getInstance() {
        if (instance == null) {
            instance = new SocialNetworkingService();
        }
        return instance;
    }

    public void registerUser(User user) {
        users.put(user.getId(), user);
    }

    public User loginUser(String email, String password) {
        for (User user : users.values()) {
            if (user.getEmail().equals(email) && user.getPassword().equals(password)) {
                return user;
            }
        }
        return null;
    }

    public void updateUserProfile(User user) {
        users.put(user.getId(), user);
    }

    public void sendFriendRequest(String senderId, String receiverId) {
        User receiver = users.get(receiverId);
        if (receiver != null) {
            Notification notification = new Notification(generateNotificationId(), receiverId,
                    NotificationType.FRIEND_REQUEST, "Friend request from " + senderId, new Timestamp(System.currentTimeMillis()));
            addNotification(receiverId, notification);
        }
    }

    public void acceptFriendRequest(String userId, String friendId) {
        User user = users.get(userId);
        User friend = users.get(friendId);
        if (user != null && friend != null) {
            user.getFriends().add(friendId);
            friend.getFriends().add(userId);
            Notification notification = new Notification(generateNotificationId(), friendId,
                    NotificationType.FRIEND_REQUEST_ACCEPTED, "Friend request accepted by " + userId,
                    new Timestamp(System.currentTimeMillis()));
            addNotification(friendId, notification);
        }
    }

    public void createPost(Post post) {
        posts.put(post.getId(), post);
        User user = users.get(post.getUserId());
        if (user != null) {
            user.getPosts().add(post);
        }
    }

    public List<Post> getNewsfeed(String userId) {
        List<Post> newsfeed = new ArrayList<>();
        User user = users.get(userId);
        if (user != null) {
            List<String> friendIds = user.getFriends();
            for (String friendId : friendIds) {
                User friend = users.get(friendId);
                if (friend != null) {
                    newsfeed.addAll(friend.getPosts());
                }
            }
            newsfeed.addAll(user.getPosts());
            newsfeed.sort((p1, p2) -> p2.getTimestamp().compareTo(p1.getTimestamp()));
        }
        return newsfeed;
    }

    public void likePost(String userId, String postId) {
        Post post = posts.get(postId);
        if (post != null && !post.getLikes().contains(userId)) {
            post.getLikes().add(userId);
            Notification notification = new Notification(generateNotificationId(), post.getUserId(),
                    NotificationType.LIKE, "Your post was liked by " + userId,
                    new Timestamp(System.currentTimeMillis()));
            addNotification(post.getUserId(), notification);
        }
    }

    public void commentOnPost(Comment comment) {
        Post post = posts.get(comment.getPostId());
        if (post != null) {
            post.getComments().add(comment);
            Notification notification = new Notification(generateNotificationId(), post.getUserId(),
                    NotificationType.COMMENT, "Your post received a comment from " + comment.getUserId(),
                    new Timestamp(System.currentTimeMillis()));
            addNotification(post.getUserId(), notification);
        }
    }

    private void addNotification(String userId, Notification notification) {
        notifications.computeIfAbsent(userId, k -> new CopyOnWriteArrayList<>()).add(notification);
    }

    public List<Notification> getNotifications(String userId) {
        return notifications.getOrDefault(userId, new ArrayList<>());
    }

    private String generateNotificationId() {
        return UUID.randomUUID().toString();
    }
}
