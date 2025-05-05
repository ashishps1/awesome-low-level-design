# Social Networking Service (LLD)

## Problem Statement

Design and implement a Social Networking Service that allows users to connect, send friend requests, post content, like and comment on posts, and receive notifications.

---

## Requirements

- **User Management:** Users can register, log in, and manage their profiles.
- **Friend Requests:** Users can send, accept, or reject friend requests.
- **Posts:** Users can create posts, which can be liked and commented on by friends.
- **Likes and Comments:** Users can like and comment on posts.
- **Notifications:** The system notifies users of friend requests, likes, comments, and other relevant events.
- **Extensibility:** Easy to add new features such as groups, messaging, or feeds.

---

## Core Entities

- **SocialNetworkingService:** Main class that manages users, posts, friend requests, and notifications.
- **User:** Represents a user with profile information, friends, posts, and notifications.
- **Post:** Represents a post created by a user, with content, likes, and comments.
- **Like:** Represents a like on a post by a user.
- **Comment:** Represents a comment on a post by a user.
- **FriendRequest:** Represents a friend request between users, with status.
- **FriendRequestStatus (enum):** PENDING, ACCEPTED, REJECTED.
- **Notification:** Represents a notification sent to a user.
- **NotificationType (enum):** Types of notifications (e.g., FRIEND_REQUEST, LIKE, COMMENT).

---

## Class Design

### 1. SocialNetworkingService
- **Fields:** List<User> users, List<Post> posts, List<FriendRequest> friendRequests, List<Notification> notifications
- **Methods:** registerUser(User), sendFriendRequest(User, User), acceptFriendRequest(FriendRequest), rejectFriendRequest(FriendRequest), createPost(User, String content), likePost(User, Post), commentOnPost(User, Post, String comment), sendNotification(Notification), etc.

### 2. User
- **Fields:** int id, String name, List<User> friends, List<Post> posts, List<Notification> notifications
- **Methods:** sendFriendRequest(User), acceptFriendRequest(FriendRequest), rejectFriendRequest(FriendRequest), createPost(String), likePost(Post), commentOnPost(Post, String), getNotifications()

### 3. Post
- **Fields:** int id, User author, String content, List<Like> likes, List<Comment> comments
- **Methods:** addLike(Like), addComment(Comment), getLikes(), getComments()

### 4. Like
- **Fields:** int id, User user, Post post

### 5. Comment
- **Fields:** int id, User user, Post post, String content

### 6. FriendRequest
- **Fields:** int id, User sender, User receiver, FriendRequestStatus status

### 7. FriendRequestStatus (enum)
- Values: PENDING, ACCEPTED, REJECTED

### 8. Notification
- **Fields:** int id, User recipient, String message, NotificationType type

### 9. NotificationType (enum)
- Values: FRIEND_REQUEST, LIKE, COMMENT, etc.

---

## Example Usage

```java
SocialNetworkingService service = new SocialNetworkingService();
User alice = new User(1, "Alice");
User bob = new User(2, "Bob");
service.registerUser(alice);
service.registerUser(bob);

service.sendFriendRequest(alice, bob);
service.acceptFriendRequest(service.getFriendRequests().get(0));

Post post = service.createPost(alice, "Hello, world!");
service.likePost(bob, post);
service.commentOnPost(bob, post, "Nice post!");
```

---

## Demo

See `SocialNetworkingServiceDemo.java` for a sample usage and simulation of the social networking service.

---

## Extending the Framework

- **Add groups:** Allow users to create and join groups.
- **Add messaging:** Support direct messaging between users.
- **Add feeds:** Implement a news feed to show posts from friends.

---