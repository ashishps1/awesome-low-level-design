from stack_overflow import StackOverflow
from user import User
from question import Question
from answer import Answer
from tag import Tag

class StackOverflowDemo:
    @staticmethod
    def run():
        stack_overflow = StackOverflow.get_instance()

        # Register users
        user1 = User(1, "john", "password123", "john@example.com", 0)
        user2 = User(2, "jane", "password456", "jane@example.com", 0)
        stack_overflow.register_user(user1)
        stack_overflow.register_user(user2)

        # User login
        logged_in_user = stack_overflow.login_user("john", "password123")
        if logged_in_user:
            print("User logged in:", logged_in_user.get_username())
        else:
            print("Invalid username or password.")

        # Post a question
        question1 = Question(1, "What is Python?", "Please explain Python.", user1, [], [], [Tag(1, "python"), Tag(2, "programming")], 0)
        stack_overflow.post_question(question1)

        # Post an answer
        answer1 = Answer(1, "Python is an interpreted high-level programming language.", user2, question1, [], 0)
        stack_overflow.post_answer(answer1)

        # Vote on the question
        stack_overflow.vote_question(question1, 1)

        # Search for questions
        search_results = stack_overflow.search_questions("Python")
        print("Search Results:")
        for question in search_results:
            print(question.get_title())

        # Get questions by tag
        tagged_questions = stack_overflow.get_questions_by_tag("python")
        print("Questions tagged with 'python':")
        for question in tagged_questions:
            print(question.get_title())

        # Get questions by user
        user_questions = stack_overflow.get_questions_by_user(user1)
        print("Questions posted by user1:")
        for question in user_questions:
            print(question.get_title())


if __name__ == "__main__":
    StackOverflowDemo.run()