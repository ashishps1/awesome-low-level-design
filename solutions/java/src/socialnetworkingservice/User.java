package socialnetworkingservice;

import java.util.List;

public class User {
    private final String id;
    private final String name;
    private final String email;
    private final String password;
    private final String profilePicture;
    private final String bio;
    private final List<String> friends;
    private final List<Post> posts;

    public User(String id, String name, String email, String password, String profilePicture, String bio, List<String> friends, List<Post> posts) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.password = password;
        this.profilePicture = profilePicture;
        this.bio = bio;
        this.friends = friends;
        this.posts = posts;
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

    public String getProfilePicture() {
        return profilePicture;
    }

    public String getBio() {
        return bio;
    }

    public List<String> getFriends() {
        return friends;
    }

    public List<Post> getPosts() {
        return posts;
    }
}
