package socialnetworkingservice.model;

import java.util.*;

public class User {
    private final String id;
    private final String name;
    private final String email;
    private final Set<User> friends = new HashSet<>();
    private final List<Post> posts = new ArrayList<>();

    public User(String name, String email) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.email = email;
    }

    public void addFriend(User friend) {
        friends.add(friend);
    }

    public  void addPost(Post post) {
        posts.add(post);
    }

    public String getId() { return id; }
    public String getName() { return name; }
    public Set<User> getFriends() { return friends; }
    public List<Post> getPosts() { return posts; }
}
