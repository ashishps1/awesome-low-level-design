package socialnetworkingservice;

import java.util.List;

public class SocialNetworkingServiceDemo {
    public static void run() {
        SocialNetworkingService socialNetworkingService = SocialNetworkingService.getInstance();

        // User registration
        User user1 = socialNetworkingService.registerUser("John Doe", "john@example.com", "password", "I love coding!");
        User user2 = socialNetworkingService.registerUser("Jane Smith", "jane@example.com", "password", "Exploring the world!");

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
        Post post1 = socialNetworkingService.createPost(user1.getId(), "My first post!");
        Post post2 = socialNetworkingService.createPost(user2.getId(), "Having a great day!");

        // Like a post
        socialNetworkingService.likePost(user2.getId(), post1.getId());

        // Comment on a post
        socialNetworkingService.commentOnPost(user2.getId(), post1.getId(), "Great post!");

        // Get newsfeed
        List<Post> newsfeed = socialNetworkingService.getNewsFeed(user2.getId());
        System.out.println("Newsfeed:");
        for (Post post : newsfeed) {
            System.out.println("Post: " + post.getContent());
            System.out.println("Likes: " + post.getLikeCount());
            System.out.println("Comments: " + post.getComments().size());
            System.out.println();
        }

        // Get notifications
        List<Notification> notifications = socialNetworkingService.getNotifications(user1.getId());
        System.out.println("Notifications:");
        for (Notification notification : notifications) {
            System.out.println("Type: " + notification.getType());
            System.out.println("Content: " + notification.getContent());
        }
    }
}
