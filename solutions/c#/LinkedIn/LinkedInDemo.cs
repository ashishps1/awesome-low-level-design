using System;
using System.Collections.Generic;

namespace LinkedInNamespace
{
    public class LinkedInDemo
    {
        public static void Run()
        {
            var linkedInService = LinkedInService.GetInstance();

            // User registration
            var user1 = new User("1", "John Doe", "john@example.com", "password", new Profile());
            var user2 = new User("2", "Jane Smith", "jane@example.com", "password", new Profile());
            linkedInService.RegisterUser(user1);
            linkedInService.RegisterUser(user2);

            // User login
            var loggedInUser = linkedInService.LoginUser("john@example.com", "password");
            Console.WriteLine(loggedInUser != null ? $"User logged in: {loggedInUser.Name}" : "Invalid email or password.");

            // Update user profile
            var profile = new Profile
            {
                Headline = "Software Engineer",
                Summary = "Passionate about coding and problem-solving."
            };
            loggedInUser.Profile = profile;
            linkedInService.UpdateUserProfile(loggedInUser);

            // Send connection request
            linkedInService.SendConnectionRequest(user1, user2);

            // Accept connection request
            linkedInService.AcceptConnectionRequest(user2, user1);

            // Post a job listing
            var jobPosting = new JobPosting("1", "Software Developer", "We are hiring!", new List<string> { "Java", "Python" }, "San Francisco", DateTime.Now);
            linkedInService.PostJobListing(jobPosting);

            // Search for users
            var searchResults = linkedInService.SearchUsers("John");
            Console.WriteLine("Search Results:");
            foreach (var user in searchResults)
            {
                Console.WriteLine($"Name: {user.Name}");
                Console.WriteLine($"Headline: {user.Profile.Headline}");
                Console.WriteLine();
            }

            // Search for job postings
            var jobPostingResults = linkedInService.SearchJobPostings("Software");
            Console.WriteLine("Job Posting Results:");
            foreach (var posting in jobPostingResults)
            {
                Console.WriteLine($"Title: {posting.Title}");
                Console.WriteLine($"Description: {posting.Description}");
                Console.WriteLine();
            }

            // Send a message
            linkedInService.SendMessage(user1, user2, "Hi Jane, hope you're doing well!");

            // Get notifications
            var notifications = linkedInService.GetNotifications(user2.Id);
            Console.WriteLine("Notifications:");
            foreach (var notification in notifications)
            {
                Console.WriteLine($"Type: {notification.Type}");
                Console.WriteLine($"Content: {notification.Content}");
                Console.WriteLine();
            }
        }
    }
}