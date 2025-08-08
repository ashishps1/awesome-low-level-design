package linkedin;

import linkedin.entities.Education;
import linkedin.entities.Experience;
import linkedin.entities.Member;
import linkedin.entities.Post;

import java.time.LocalDate;
import java.util.List;

public class LinkedInDemo {
    public static void main(String[] args) {
        LinkedInSystem system = LinkedInSystem.getInstance();

        // --- 1. Create Members using the Builder Pattern ---
        System.out.println("--- 1. Member Registration ---");
        Member alice = new Member.Builder("Alice", "alice@example.com")
                .withSummary("Senior Software Engineer with 10 years of experience.")
                .addExperience(new Experience("Sr. Software Engineer", "Google", LocalDate.of(2018, 1, 1), null))
                .addExperience(new Experience("Software Engineer", "Microsoft", LocalDate.of(2014, 6, 1), LocalDate.of(2017, 12, 31)))
                .addEducation(new Education("Princeton University", "M.S. in Computer Science", 2012, 2014))
                .build();

        Member bob = new Member.Builder("Bob", "bob@example.com")
                .withSummary("Product Manager at Stripe.")
                .addExperience(new Experience("Product Manager", "Stripe", LocalDate.of(2020, 2, 1), null))
                .addEducation(new Education("MIT", "B.S. in Business Analytics", 2015, 2019))
                .build();

        Member charlie = new Member.Builder("Charlie", "charlie@example.com").build();

        system.registerMember(alice);
        system.registerMember(bob);
        system.registerMember(charlie);

        alice.displayProfile();

        // --- 2. Connection Management ---
        System.out.println("\n--- 2. Connection Management ---");
        // Alice sends requests to Bob and Charlie
        String requestId1 = system.sendConnectionRequest(alice, bob);
        String requestId2 = system.sendConnectionRequest(alice, charlie);

        bob.viewNotifications(); // Bob sees Alice's request.

        System.out.println("\nBob accepts Alice's request.");
        system.acceptConnectionRequest(requestId1);
        System.out.println("Alice and Bob are now connected.");

        // --- 3. Posting and News Feed ---
        System.out.println("\n--- 3. Posting & News Feed ---");
        bob.displayProfile(); // Bob has 1 connection
        system.createPost(bob.getId(), "Excited to share we've launched our new feature! #productmanagement");

        // Alice views her news feed. She should see Bob's post.
        system.viewNewsFeed(alice.getId());

        // Charlie views his feed. It should be empty as he is not connected to anyone.
        system.viewNewsFeed(charlie.getId());

        // --- 4. Interacting with a Post (Observer Pattern in action) ---
        System.out.println("\n--- 4. Post Interaction & Notifications ---");
        Post bobsPost = system.getLatestPostByMember(bob.getId());
        if (bobsPost != null) {
            bobsPost.addLike(alice);
            bobsPost.addComment(alice, "This looks amazing! Great work!");
        }

        // Bob checks his notifications. He should see a like and a comment from Alice.
        bob.viewNotifications();

        // --- 5. Searching for Members ---
        System.out.println("\n--- 5. Member Search ---");
        List<Member> searchResults = system.searchMemberByName("ali");
        System.out.println("Search results for 'ali':");
        searchResults.forEach(m -> System.out.println(" - " + m.getName()));
    }
}
