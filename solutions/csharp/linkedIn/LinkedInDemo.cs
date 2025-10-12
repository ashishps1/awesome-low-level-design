using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class LinkedInDemo
{
    public static void Main(string[] args)
    {
        var system = LinkedInSystem.GetInstance();

        // 1. Create Members using the Builder Pattern
        Console.WriteLine("--- 1. Member Registration ---");
        var alice = new MemberBuilder("Alice", "alice@example.com")
            .WithSummary("Senior Software Engineer with 10 years of experience.")
            .AddExperience(new Experience("Sr. Software Engineer", "Google", "2018-01-01", null))
            .AddExperience(new Experience("Software Engineer", "Microsoft", "2014-06-01", "2017-12-31"))
            .AddEducation(new Education("Princeton University", "M.S. in Computer Science", 2012, 2014))
            .Build();

        var bob = new MemberBuilder("Bob", "bob@example.com")
            .WithSummary("Product Manager at Stripe.")
            .AddExperience(new Experience("Product Manager", "Stripe", "2020-02-01", null))
            .AddEducation(new Education("MIT", "B.S. in Business Analytics", 2015, 2019))
            .Build();

        var charlie = new MemberBuilder("Charlie", "charlie@example.com").Build();

        system.RegisterMember(alice);
        system.RegisterMember(bob);
        system.RegisterMember(charlie);

        alice.DisplayProfile();

        // 2. Connection Management
        Console.WriteLine("\n--- 2. Connection Management ---");
        string requestId1 = system.SendConnectionRequest(alice, bob);
        string requestId2 = system.SendConnectionRequest(alice, charlie);

        bob.ViewNotifications();

        Console.WriteLine("\nBob accepts Alice's request.");
        system.AcceptConnectionRequest(requestId1);
        Console.WriteLine("Alice and Bob are now connected.");

        // 3. Posting and News Feed
        Console.WriteLine("\n--- 3. Posting & News Feed ---");
        bob.DisplayProfile();
        system.CreatePost(bob.GetId(), "Excited to share we've launched our new feature! #productmanagement");

        system.ViewNewsFeed(alice.GetId());
        system.ViewNewsFeed(charlie.GetId());

        // 4. Interacting with a Post
        Console.WriteLine("\n--- 4. Post Interaction & Notifications ---");
        var bobsPost = system.GetLatestPostByMember(bob.GetId());
        if (bobsPost != null)
        {
            bobsPost.AddLike(alice);
            bobsPost.AddComment(alice, "This looks amazing! Great work!");
        }

        bob.ViewNotifications();

        // 5. Searching for Members
        Console.WriteLine("\n--- 5. Member Search ---");
        var searchResults = system.SearchMemberByName("ali");
        Console.WriteLine("Search results for 'ali':");
        foreach (var member in searchResults)
        {
            Console.WriteLine($" - {member.GetName()}");
        }
    }
}