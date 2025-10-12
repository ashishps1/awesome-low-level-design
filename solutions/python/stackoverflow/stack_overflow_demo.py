from stack_overflow_service import StackOverflowService
from enums import VoteType
from search_strategy import UserSearchStrategy, TagSearchStrategy
from tag import Tag

class StackOverflowDemo:
    @staticmethod
    def main():
        service = StackOverflowService()

        # 1. Create Users
        alice = service.create_user("Alice")
        bob = service.create_user("Bob")
        charlie = service.create_user("Charlie")

        # 2. Alice posts a question
        print("--- Alice posts a question ---")
        java_tag = Tag("java")
        design_patterns_tag = Tag("design-patterns")
        tags = {java_tag, design_patterns_tag}
        question = service.post_question(alice.get_id(), "How to implement Observer Pattern?", "Details about Observer Pattern...", tags)
        StackOverflowDemo.print_reputations(alice, bob, charlie)

        # 3. Bob and Charlie post answers
        print("\n--- Bob and Charlie post answers ---")
        bob_answer = service.post_answer(bob.get_id(), question.get_id(), "You can use the java.util.Observer interface.")
        charlie_answer = service.post_answer(charlie.get_id(), question.get_id(), "A better way is to create your own Observer interface.")
        StackOverflowDemo.print_reputations(alice, bob, charlie)

        # 4. Voting happens
        print("\n--- Voting Occurs ---")
        service.vote_on_post(alice.get_id(), question.get_id(), VoteType.UPVOTE)  # Alice upvotes her own question
        service.vote_on_post(bob.get_id(), charlie_answer.get_id(), VoteType.UPVOTE)  # Bob upvotes Charlie's answer
        service.vote_on_post(alice.get_id(), bob_answer.get_id(), VoteType.DOWNVOTE)  # Alice downvotes Bob's answer
        StackOverflowDemo.print_reputations(alice, bob, charlie)

        # 5. Alice accepts Charlie's answer
        print("\n--- Alice accepts Charlie's answer ---")
        service.accept_answer(question.get_id(), charlie_answer.get_id())
        StackOverflowDemo.print_reputations(alice, bob, charlie)

        # 6. Search for questions
        print("\n--- (C) Combined Search: Questions by 'Alice' with tag 'java' ---")
        filters_c = [
            UserSearchStrategy(alice),
            TagSearchStrategy(java_tag)
        ]
        search_results = service.search_questions(filters_c)
        for q in search_results:
            print(f"  - Found: {q.get_title()}")

    @staticmethod
    def print_reputations(*users):
        print("--- Current Reputations ---")
        for user in users:
            print(f"{user.get_name()}: {user.get_reputation()}")


if __name__ == "__main__":
    StackOverflowDemo.main()