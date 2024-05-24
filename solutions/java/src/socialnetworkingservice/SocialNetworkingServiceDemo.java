package socialnetworkingservice;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.List;

public class SocialNetworkingServiceDemo {
    public static void run() {
        SocialNetworkingService socialNetworkingService = SocialNetworkingService.getInstance();

        // User registration
        User user1 = new User("1", "John Doe", "john@example.com", "password", "profile1.jpg", "I love coding!", new ArrayList<>(), new ArrayList<>());
        User user2 = new User("2", "Jane Smith", "jane@example.com", "password", "profile2.jpg", "Exploring the world!", new ArrayList<>(), new ArrayList<>());
        socialNetworkingService.registerUser(user1);
        socialNetworkingService.registerUser(user2);

        // User login
        User loggedInUser = socialNetworkingService.loginUser("john@example.com", "password");
        if (loggedInUser != null) {
            System.out.println("User logged in: " + loggedInUser.getName());
        } else {
            System.out.println("Invalid email or password.");
        }

        // Send friend request
        socialNetworkingService.sendFriendRequest(user1.getId(), user2.getId());

        // Accept friend request
        socialNetworkingService.acceptFriendRequest(user2.getId(), user1.getId());

        // Create posts
        Post post1 = new Post("post1", user1.getId(), "My first post!", new ArrayList<>(), new ArrayList<>(), new Timestamp(System.currentTimeMillis()), new ArrayList<>(), new ArrayList<>());
        Post post2 = new Post("post2", user2.getId(), "Having a great day!", new ArrayList<>(), new ArrayList<>(), new Timestamp(System.currentTimeMillis()), new ArrayList<>(), new ArrayList<>());
        socialNetworkingService.createPost(post1);
        socialNetworkingService.createPost(post2);

        // Like a post
        socialNetworkingService.likePost(user2.getId(), post1.getId());

        // Comment on a post
        Comment comment = new Comment("comment1", user2.getId(), post1.getId(), "Great post!", new Timestamp(System.currentTimeMillis()));
        socialNetworkingService.commentOnPost(comment);

        // Get newsfeed
        List<Post> newsfeed = socialNetworkingService.getNewsfeed(user1.getId());
        System.out.println("Newsfeed:");
        for (Post post : newsfeed) {
            System.out.println("Post: " + post.getContent());
            System.out.println("Likes: " + post.getLikes().size());
            System.out.println("Comments: " + post.getComments().size());
            System.out.println();
        }

        // Get notifications
        List<Notification> notifications = socialNetworkingService.getNotifications(user1.getId());
        System.out.println("Notifications:");
        for (Notification notification : notifications) {
            System.out.println("Type: " + notification.getType());
            System.out.println("Content: " + notification.getContent());
            System.out.println();
        }
    }
}
