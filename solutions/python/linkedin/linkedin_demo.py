from datetime import datetime
from linkedin_service import LinkedInService
from user import User
from profile import Profile
from job_posting import JobPosting

class LinkedInDemo:
    @staticmethod
    def run():
        linkedin_service = LinkedInService()

        # User registration
        user1 = User("1", "John Doe", "john@example.com", "password", Profile(), [], [], [])
        user2 = User("2", "Jane Smith", "jane@example.com", "password", Profile(), [], [], [])
        linkedin_service.register_user(user1)
        linkedin_service.register_user(user2)

        # User login
        logged_in_user = linkedin_service.login_user("john@example.com", "password")
        if logged_in_user:
            print(f"User logged in: {logged_in_user.name}")
        else:
            print("Invalid email or password.")

        # Update user profile
        profile = Profile()
        profile.set_headline("Software Engineer")
        profile.set_summary("Passionate about coding and problem-solving.")
        logged_in_user.set_profile(profile)
        linkedin_service.update_user_profile(logged_in_user)

        # Send connection request
        linkedin_service.send_connection_request(user1, user2)

        # Accept connection request
        linkedin_service.accept_connection_request(user2, user1)

        # Post a job listing
        job_posting = JobPosting("1", "Software Developer", "We are hiring!", ["Java", "Python"], "San Francisco", datetime.now())
        linkedin_service.post_job_listing(job_posting)

        # Search for users
        search_results = linkedin_service.search_users("John")
        print("Search Results:")
        for user in search_results:
            print(f"Name: {user.name}")
            print(f"Headline: {user.profile.headline}")
            print()

        # Search for job postings
        job_posting_results = linkedin_service.search_job_postings("Software")
        print("Job Posting Results:")
        for posting in job_posting_results:
            print(f"Title: {posting.title}")
            print(f"Description: {posting.description}")
            print()

        # Send a message
        linkedin_service.send_message(user1, user2, "Hi Jane, hope you're doing well!")

        # Get notifications
        notifications = linkedin_service.get_notifications(user2.id)
        print("Notifications:")
        for notification in notifications:
            print(f"Type: {notification.type}")
            print(f"Content: {notification.content}")
            print()

if __name__ == "__main__":
    LinkedInDemo.run()
