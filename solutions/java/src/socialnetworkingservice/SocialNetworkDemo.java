package socialnetworkingservice;

import socialnetworkingservice.model.Post;
import socialnetworkingservice.model.User;

import java.util.List;

public class SocialNetworkDemo {
    public static void main(String[] args) {
        SocialNetworkFacade socialNetwork = new SocialNetworkFacade();

        System.out.println("----------- 1. Creating Users -----------");
        User alice = socialNetwork.createUser("Alice", "alice@example.com");
        User bob = socialNetwork.createUser("Bob", "bob@example.com");
        User charlie = socialNetwork.createUser("Charlie", "charlie@example.com");
        System.out.println("Created users: " + alice.getName() + ", " + bob.getName() + ", " + charlie.getName());

        System.out.println("\n----------- 2. Building Friendships -----------");
        socialNetwork.addFriend(alice.getId(), bob.getId());
        socialNetwork.addFriend(bob.getId(), charlie.getId());
        System.out.println(alice.getName() + " and " + bob.getName() + " are now friends.");
        System.out.println(bob.getName() + " and " + charlie.getName() + " are now friends.");

        System.out.println("\n----------- 3. Users Create Posts -----------");
        Post alicePost = socialNetwork.createPost(alice.getId(), "Hello from Alice!");
        Post bobPost = socialNetwork.createPost(bob.getId(), "It's a beautiful day!");
        Post charliePost = socialNetwork.createPost(charlie.getId(), "Thinking about design patterns.");

        System.out.println("\n----------- 4. Users Interact with Posts -----------");
        socialNetwork.addComment(bob.getId(), alicePost.getId(), "Hey Alice, nice to see you here!");
        socialNetwork.likePost(charlie.getId(), alicePost.getId());

        System.out.println("\n----------- 5. Viewing News Feeds (Strategy Pattern) -----------");

        System.out.println("\n--- Alice's News Feed (should see Bob's post) ---");
        List<Post> alicesFeed = socialNetwork.getNewsFeed(alice.getId());
        printFeed(alicesFeed);

        System.out.println("\n--- Bob's News Feed (should see Alice's, and Charlie's post) ---");
        List<Post> bobsFeed = socialNetwork.getNewsFeed(bob.getId());
        printFeed(bobsFeed);

        System.out.println("\n--- Charlie's News Feed (should see Bob's post) ---");
        List<Post> charliesFeed = socialNetwork.getNewsFeed(charlie.getId());
        printFeed(charliesFeed);
    }

    private static void printFeed(List<Post> feed) {
        if (feed.isEmpty()) {
            System.out.println("  No posts in the feed.");
            return;
        }
        feed.forEach(post -> {
            System.out.println("  Post by " + post.getAuthor().getName() + " at " + post.getTimestamp());
            System.out.println("    \"" + post.getContent() + "\"");
            System.out.println("    Likes: " + post.getLikes().size() + ", Comments: " + post.getComments().size());
        });
    }
}
