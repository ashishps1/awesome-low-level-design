package socialnetworkingservice;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class User {
    private final String id;
    private final String name;
    private final String email;
    private final String password;
    private final String bio;
    private final Set<User> friends;
    private final Map<String, Post> postsMap;
    private final List<FriendRequest> friendRequests;
    private final List<Notification> notifications;

    public User(String name, String email, String password, String bio) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.email = email;
        this.password = password;
        this.bio = bio;
        this.friends = ConcurrentHashMap.newKeySet();;
        this.postsMap = new ConcurrentHashMap<>();
        this.friendRequests = Collections.synchronizedList(new ArrayList<>());
        this.notifications = Collections.synchronizedList(new ArrayList<>());
    }

    public void addFriend(User user) {
        friends.add(user);
    }

    public boolean isFriend(User user) {
        return friends.contains(user);
    }

    public void addPost(Post post) {
        postsMap.put(post.getId(), post);
    }

    public Post getPost(String postId) {
        return postsMap.get(postId);
    }

    public List<Post> getPosts() {
        return postsMap.values().stream().toList();
    }

    public void receiveRequest(FriendRequest req) {
        friendRequests.add(req);
    }

    public FriendRequest getRequestFrom(User user) {
        for (FriendRequest r : friendRequests) {
            if (r.getFrom().equals(user) && r.getStatus() == FriendRequestStatus.PENDING) return r;
        }
        return null;
    }

    public void addNotification(Notification notification) {
        notifications.add(notification);
    }

    public List<Notification> getNotifications() {
        return notifications;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public String getPassword() {
        return password;
    }

    public String getBio() {
        return bio;
    }

    public List<User> getFriends() {
        return friends.stream().toList();
    }
}
