from datetime import datetime
from linkedin_service import LinkedInService
from user import User
from profile import Profile
from job_posting import JobPosting

class LinkedInDemo:
    @staticmethod
    def run():
        linked_in_service = LinkedInService.get_instance()

        # User registration
        user1 = User("1", "John Doe", "john@example.com", "password", Profile(), [], [], [])
        user2 = User("2", "Jane Smith", "jane@example.com", "password", Profile(), [], [], [])
        linked_in_service.register_user(user1)
        linked_in_service.register_user(user2)

        # User login
        logged_in_user = linked_in_service.login_user("john@example.com", "password")
        if logged_in_user:
            print("User logged in:", logged_in_user.name)
        else:
            print("Invalid email or password.")

        # Update user profile
        profile = Profile()
        profile.headline = "Software Engineer"
        profile.summary = "Passionate about coding and problem-solving."
        logged_in_user.profile = profile
        linked_in_service.update_user_profile(logged_in_user)

        # Send connection request
        linked_in_service.send_connection_request(user1, user2)

        # Accept connection request
        linked_in_service.accept_connection_request(user2, user1)

        # Post a job listing
        job_posting = JobPosting("1", "Software Developer", "We are hiring!", ["Java", "Python"], "San Francisco", datetime.now())
        linked_in_service.post_job_listing(job_posting)

        # Search for users
        search_results = linked_in_service.search_users("John")
        print("Search Results:")
        for user in search_results:
            print("Name:", user.name)
            print("Headline:", user.profile.headline)
            print()

        # Search for job postings
        job_posting_results = linked_in_service.search_job_postings("Software")
        print("Job Posting Results:")
        for posting in job_posting_results:
            print("Title:", posting.title)
            print("Description:", posting.description)
            print()

        # Send a message
        linked_in_service.send_message(user1, user2, "Hi Jane, hope you're doing well!")

        # Get notifications
        notifications = linked_in_service.get_notifications(user2.id)
        print("Notifications:")
        for notification in notifications:
            print("Type:", notification.type)
            print("Content:", notification.content)
            print()

if __name__ == "__main__":
    LinkedInDemo.run()
