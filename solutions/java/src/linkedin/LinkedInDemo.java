package linkedin;

import java.sql.Timestamp;
import java.util.Arrays;
import java.util.List;

public class LinkedInDemo {
    public static void run() {
        LinkedInService linkedInService = LinkedInService.getInstance();

        // User registration
        User user1 = linkedInService.registerUser("John Doe", "john@example.com", "password");
        User user2 = linkedInService.registerUser("Jane Smith", "jane@example.com", "password");

        // Set user profile
        Profile profile = new Profile();
        profile.setHeadline("Software Engineer");
        profile.setSummary("Passionate about coding and problem-solving.");
        user1.setProfile(profile);

        // Send connection request
        linkedInService.sendConnectionRequest(user1, user2);

        // Accept connection request
        linkedInService.acceptConnectionRequest(user2, user1);

        // Post a job listing
        JobPosting jobPosting1 = linkedInService.postJobListing("Software Developer", "Discord", "AI Engineer", "San Francisco");
        JobPosting jobPosting2 = linkedInService.postJobListing("Software Developer", "Airbnb", "Full Stack Developer", "Seattle");

        // Search for users
        List<User> searchResults = linkedInService.searchUsers("John");
        System.out.println("Search Results:");
        for (User user : searchResults) {
            System.out.println("Name: " + user.getName());
            System.out.println("Headline: " + user.getProfile().getHeadline());
            System.out.println();
        }

        // Search for job postings
        List<JobPosting> jobPostingResults = linkedInService.searchJobPostings("Software");
        System.out.println("Job Posting Results:");
        for (JobPosting posting : jobPostingResults) {
            System.out.println("Title: " + posting.getTitle());
            System.out.println("Description: " + posting.getDescription());
            System.out.println();
        }

        // Send a message
        linkedInService.sendMessage(user1, user2, "Hi Jane, hope you're doing well!");

        // Get notifications
        List<Notification> notifications = linkedInService.getNotifications(user2.getId());
        System.out.println("Notifications:");
        for (Notification notification : notifications) {
            System.out.println("Type: " + notification.getType());
            System.out.println("Content: " + notification.getContent());
            System.out.println();
        }
    }
}
