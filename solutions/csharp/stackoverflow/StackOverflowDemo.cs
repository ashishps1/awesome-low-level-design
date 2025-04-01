using System;
using System.Collections.Generic;

namespace StackOverflow
{
    public class StackOverflowDemo
    {
        public static void Run()
        {
            var system = new StackOverflowSystem();

            // Create users
            var alice = system.CreateUser("Alice", "alice@example.com");
            var bob = system.CreateUser("Bob", "bob@example.com");
            var charlie = system.CreateUser("Charlie", "charlie@example.com");

            // Alice asks a question
            var javaQuestion = system.AskQuestion(alice, "What is polymorphism in Java?",
                "Can someone explain polymorphism in Java with an example?",
                new List<string> { "java", "oop" });

            // Bob answers Alice's question
            var bobAnswer = system.AnswerQuestion(bob, javaQuestion,
                "Polymorphism in Java is the ability of an object to take on many forms...");

            // Charlie comments on the question
            system.AddComment(charlie, javaQuestion, "Great question! I'm also interested in learning about this.");

            // Alice comments on Bob's answer
            system.AddComment(alice, bobAnswer, "Thanks for the explanation! Could you provide a code example?");

            // Charlie votes on the question and answer
            system.VoteQuestion(charlie, javaQuestion, 1);  // Upvote
            system.VoteAnswer(charlie, bobAnswer, 1);  // Upvote

            // Alice accepts Bob's answer
            system.AcceptAnswer(bobAnswer);

            // Bob asks another question
            var pythonQuestion = system.AskQuestion(bob, "How to use list comprehensions in Python?",
                "I'm new to Python and I've heard about list comprehensions. Can someone explain how to use them?",
                new List<string> { "python", "list-comprehension" });

            // Alice answers Bob's question
            var aliceAnswer = system.AnswerQuestion(alice, pythonQuestion,
                "List comprehensions in Python provide a concise way to create lists...");

            // Charlie votes on Bob's question and Alice's answer
            system.VoteQuestion(charlie, pythonQuestion, 1);  // Upvote
            system.VoteAnswer(charlie, aliceAnswer, 1);  // Upvote

            // Print out the current state
            Console.WriteLine($"Question: {javaQuestion.Title}");
            Console.WriteLine($"Asked by: {javaQuestion.Author.Username}");
            Console.WriteLine($"Tags: {string.Join(", ", javaQuestion.Tags)}");
            Console.WriteLine($"Votes: {javaQuestion.GetVoteCount()}");
            Console.WriteLine($"Comments: {javaQuestion.GetComments().Count}");
            Console.WriteLine($"\nAnswer by {bobAnswer.Author.Username}:");
            Console.WriteLine(bobAnswer.Content);
            Console.WriteLine($"Votes: {bobAnswer.GetVoteCount()}");
            Console.WriteLine($"Accepted: {bobAnswer.IsAccepted}");
            Console.WriteLine($"Comments: {bobAnswer.GetComments().Count}");

            Console.WriteLine("\nUser Reputations:");
            Console.WriteLine($"Alice: {alice.Reputation}");
            Console.WriteLine($"Bob: {bob.Reputation}");
            Console.WriteLine($"Charlie: {charlie.Reputation}");

            // Demonstrate search functionality
            Console.WriteLine("\nSearch Results for 'java':");
            var searchResults = system.SearchQuestions("java");
            foreach (var question in searchResults)
            {
                Console.WriteLine(question.Title);
            }

            Console.WriteLine("\nSearch Results for 'python':");
            searchResults = system.SearchQuestions("python");
            foreach (var question in searchResults)
            {
                Console.WriteLine(question.Title);
            }

            // Demonstrate getting questions by user
            Console.WriteLine("\nBob's Questions:");
            var bobQuestions = system.GetQuestionsByUser(bob);
            foreach (var question in bobQuestions)
            {
                Console.WriteLine(question.Title);
            }
        }
    }
}