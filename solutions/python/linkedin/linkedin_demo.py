from linkedin_system import LinkedInSystem
from member import Member
from experience import Experience
from education import Education
from datetime import date

class LinkedInDemo:
    @staticmethod
    def main():
        system = LinkedInSystem.get_instance()

        # 1. Create Members using the Builder Pattern
        print("--- 1. Member Registration ---")
        alice = Member.Builder("Alice", "alice@example.com") \
            .with_summary("Senior Software Engineer with 10 years of experience.") \
            .add_experience(Experience("Sr. Software Engineer", "Google", date(2018, 1, 1), None)) \
            .add_experience(Experience("Software Engineer", "Microsoft", date(2014, 6, 1), date(2017, 12, 31))) \
            .add_education(Education("Princeton University", "M.S. in Computer Science", 2012, 2014)) \
            .build()

        bob = Member.Builder("Bob", "bob@example.com") \
            .with_summary("Product Manager at Stripe.") \
            .add_experience(Experience("Product Manager", "Stripe", date(2020, 2, 1), None)) \
            .add_education(Education("MIT", "B.S. in Business Analytics", 2015, 2019)) \
            .build()

        charlie = Member.Builder("Charlie", "charlie@example.com").build()

        system.register_member(alice)
        system.register_member(bob)
        system.register_member(charlie)

        alice.display_profile()

        # 2. Connection Management
        print("\n--- 2. Connection Management ---")
        # Alice sends requests to Bob and Charlie
        request_id1 = system.send_connection_request(alice, bob)
        request_id2 = system.send_connection_request(alice, charlie)

        bob.view_notifications()  # Bob sees Alice's request

        print("\nBob accepts Alice's request.")
        system.accept_connection_request(request_id1)
        print("Alice and Bob are now connected.")

        # 3. Posting and News Feed
        print("\n--- 3. Posting & News Feed ---")
        bob.display_profile()  # Bob has 1 connection
        system.create_post(bob.get_id(), "Excited to share we've launched our new feature! #productmanagement")

        # Alice views her news feed. She should see Bob's post.
        system.view_news_feed(alice.get_id())

        # Charlie views his feed. It should be empty as he is not connected to anyone.
        system.view_news_feed(charlie.get_id())

        # 4. Interacting with a Post (Observer Pattern in action)
        print("\n--- 4. Post Interaction & Notifications ---")
        bobs_post = system.get_latest_post_by_member(bob.get_id())
        if bobs_post:
            bobs_post.add_like(alice)
            bobs_post.add_comment(alice, "This looks amazing! Great work!")

        # Bob checks his notifications. He should see a like and a comment from Alice.
        bob.view_notifications()

        # 5. Searching for Members
        print("\n--- 5. Member Search ---")
        search_results = system.search_member_by_name("ali")
        print("Search results for 'ali':")
        for member in search_results:
            print(f" - {member.get_name()}")

if __name__ == "__main__":
    LinkedInDemo.main()