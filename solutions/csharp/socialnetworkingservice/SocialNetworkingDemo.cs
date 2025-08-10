using System;
using System.Collections.Generic;
using System.Linq;

public class SocialNetworkDemo
{
    private static void PrintFeed(List<Post> feed)
    {
        if (feed.Count == 0)
        {
            Console.WriteLine("  No posts in the feed.");
            return;
        }

        foreach (Post post in feed)
        {
            Console.WriteLine($"  Post by {post.GetAuthor().GetName()} at {post.GetTimestamp()}");
            Console.WriteLine($"    \"{post.GetContent()}\"");
            Console.WriteLine($"    Likes: {post.GetLikes().Count}, Comments: {post.GetComments().Count}");
        }
    }

    public static void Main(string[] args)
    {
        SocialNetworkFacade socialNetwork = new SocialNetworkFacade();

        Console.WriteLine("----------- 1. Creating Users -----------");
        User alice = socialNetwork.CreateUser("Alice", "alice@example.com");
        User bob = socialNetwork.CreateUser("Bob", "bob@example.com");
        User charlie = socialNetwork.CreateUser("Charlie", "charlie@example.com");
        Console.WriteLine($"Created users: {alice.GetName()}, {bob.GetName()}, {charlie.GetName()}");

        Console.WriteLine("\n----------- 2. Building Friendships -----------");
        socialNetwork.AddFriend(alice.GetId(), bob.GetId());
        socialNetwork.AddFriend(bob.GetId(), charlie.GetId());
        Console.WriteLine($"{alice.GetName()} and {bob.GetName()} are now friends.");
        Console.WriteLine($"{bob.GetName()} and {charlie.GetName()} are now friends.");

        Console.WriteLine("\n----------- 3. Users Create Posts -----------");
        Post alicePost = socialNetwork.CreatePost(alice.GetId(), "Hello from Alice!");
        Post bobPost = socialNetwork.CreatePost(bob.GetId(), "It's a beautiful day!");
        Post charliePost = socialNetwork.CreatePost(charlie.GetId(), "Thinking about design patterns.");

        Console.WriteLine("\n----------- 4. Users Interact with Posts -----------");
        socialNetwork.AddComment(bob.GetId(), alicePost.GetId(), "Hey Alice, nice to see you here!");
        socialNetwork.LikePost(charlie.GetId(), alicePost.GetId());

        Console.WriteLine("\n----------- 5. Viewing News Feeds (Strategy Pattern) -----------");

        Console.WriteLine("\n--- Alice's News Feed (should see Bob's post) ---");
        List<Post> alicesFeed = socialNetwork.GetNewsFeed(alice.GetId());
        PrintFeed(alicesFeed);

        Console.WriteLine("\n--- Bob's News Feed (should see Alice's, and Charlie's post) ---");
        List<Post> bobsFeed = socialNetwork.GetNewsFeed(bob.GetId());
        PrintFeed(bobsFeed);

        Console.WriteLine("\n--- Charlie's News Feed (should see Bob's post) ---");
        List<Post> charliesFeed = socialNetwork.GetNewsFeed(charlie.GetId());
        PrintFeed(charliesFeed);
    }
}