# Designing a Social Network Like Facebook

This article explores designing and implementing a social network platform similar to Facebook using Java. 

We focus on user profiles, friendships, posting updates, and generating a feed of posts.

## System Requirements

The Social Network platform should support:

1. **User Profile Management:** Enabling creation and management of user profiles.
2. **Friendship Management:** Allowing users to connect as friends.
3. **Posting Updates:** Permitting users to post updates and view others' updates.
4. **Feed Generation:** Displaying a feed composed of friends' posts.

## Core Use Cases

1. **Creating and Updating User Profiles**
2. **Managing Friendships**
3. **Creating Posts**
4. **Viewing the Feed**

## Key Classes:
- `SocialNetworkSystem`: Manages the overall operations.
- `User`: Represents a user on the network.
- `Post`: Represents a user's post.
- `Friendship`: Manages the friendships between users.

## Java Implementation

### User Class

Handles user profiles and interactions.

```java
public class User {
    private String userId;
    private String name;
    private List<User> friends;
    private List<Post> posts;

    public User(String name) {
        this.userId = generateUserId();
        this.name = name;
        this.friends = new ArrayList<>();
        this.posts = new ArrayList<>();
    }

    public void addFriend(User user) {
        friends.add(user);
    }

    public void postUpdate(String content) {
        posts.add(new Post(this, content));
    }

    private String generateUserId() {
        return "USR_" + System.currentTimeMillis();
    }

    // Getters and setters...
}
```
### Post Class
Represents a post on the social network.
```java
public class Post {
    private User author;
    private String content;
    private long timestamp;

    public Post(User author, String content) {
        this.author = author;
        this.content = content;
        this.timestamp = System.currentTimeMillis();
    }

    // Getters and setters...
}
```
### Friendship Class
Manages connections between users.
```java
public class Friendship {
    private User user1;
    private User user2;

    public Friendship(User user1, User user2) {
        this.user1 = user1;
        this.user2 = user2;
        establishFriendship();
    }

    private void establishFriendship() {
        user1.addFriend(user2);
        user2.addFriend(user1);
    }

    // Getters and setters...
}
```
### SocialNetworkSystem Class
Main class for managing the network.
```java
import java.util.ArrayList;
import java.util.List;

public class SocialNetworkSystem {
    private List<User> users;
    private List<Friendship> friendships;

    public SocialNetworkSystem() {
        users = new ArrayList<>();
        friendships = new ArrayList<>();
    }

    public void addUser(User user) {
        users.add(user);
    }

    public void addFriendship(Friendship friendship) {
        friendships.add(friendship);
    }

    public List<Post> getFeed(User user) {
        List<Post> feed = new ArrayList<>();
        for (User friend : user.getFriends()) {
            feed.addAll(friend.getPosts());
        }
        return feed;
    }

    // Other necessary methods...
}
```