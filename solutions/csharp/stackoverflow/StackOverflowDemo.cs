using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

public class StackOverflowDemo
{
    public static void Main(string[] args)
    {
        StackOverflowService service = new StackOverflowService();

        // 1. Create Users
        User alice = service.CreateUser("Alice");
        User bob = service.CreateUser("Bob");
        User charlie = service.CreateUser("Charlie");

        // 2. Alice posts a question
        Console.WriteLine("--- Alice posts a question ---");
        Tag javaTag = new Tag("java");
        Tag designPatternsTag = new Tag("design-patterns");
        HashSet<Tag> tags = new HashSet<Tag> { javaTag, designPatternsTag };
        Question question = service.PostQuestion(alice.GetId(), "How to implement Observer Pattern?", "Details about Observer Pattern...", tags);
        PrintReputations(alice, bob, charlie);

        // 3. Bob and Charlie post answers
        Console.WriteLine("\n--- Bob and Charlie post answers ---");
        Answer bobAnswer = service.PostAnswer(bob.GetId(), question.GetId(), "You can use the java.util.Observer interface.");
        Answer charlieAnswer = service.PostAnswer(charlie.GetId(), question.GetId(), "A better way is to create your own Observer interface.");
        PrintReputations(alice, bob, charlie);

        // 4. Voting happens
        Console.WriteLine("\n--- Voting Occurs ---");
        service.VoteOnPost(alice.GetId(), question.GetId(), VoteType.UPVOTE);
        service.VoteOnPost(bob.GetId(), charlieAnswer.GetId(), VoteType.UPVOTE);
        service.VoteOnPost(alice.GetId(), bobAnswer.GetId(), VoteType.DOWNVOTE);
        PrintReputations(alice, bob, charlie);

        // 5. Alice accepts Charlie's answer
        Console.WriteLine("\n--- Alice accepts Charlie's answer ---");
        service.AcceptAnswer(question.GetId(), charlieAnswer.GetId());
        PrintReputations(alice, bob, charlie);

        // 6. Search for questions
        Console.WriteLine("\n--- (C) Combined Search: Questions by 'Alice' with tag 'java' ---");
        List<ISearchStrategy> filtersC = new List<ISearchStrategy>
        {
            new UserSearchStrategy(alice),
            new TagSearchStrategy(javaTag)
        };
        List<Question> searchResults = service.SearchQuestions(filtersC);
        foreach (var q in searchResults)
        {
            Console.WriteLine($"  - Found: {q.GetTitle()}");
        }
    }

    private static void PrintReputations(params User[] users)
    {
        Console.WriteLine("--- Current Reputations ---");
        foreach (User user in users)
        {
            Console.WriteLine($"{user.GetName()}: {user.GetReputation()}");
        }
    }
}