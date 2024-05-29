from collections import defaultdict

class StackOverflow:
    _instance = None

    def __init__(self):
        if StackOverflow._instance is not None:
            raise Exception("This class is a singleton!")
        else:
            StackOverflow._instance = self
            self.users = {}
            self.questions = {}
            self.tagged_questions = defaultdict(list)

    @staticmethod
    def get_instance():
        if StackOverflow._instance is None:
            StackOverflow()
        return StackOverflow._instance

    def register_user(self, user):
        self.users[user.get_id()] = user

    def login_user(self, username, password):
        for user in self.users.values():
            if user.get_username() == username and user.get_password() == password:
                return user
        return None

    def post_question(self, question):
        self.questions[question.get_id()] = question
        for tag in question.get_tags():
            self.tagged_questions[tag.get_name()].append(question)

    def post_answer(self, answer):
        question = answer.get_question()
        question.get_answers().append(answer)

    def post_comment(self, comment):
        # Add comment to the respective question or answer
        # ...
        pass

    def vote_question(self, question, value):
        question.set_vote_count(question.get_vote_count() + value)
        self.update_user_reputation(question.get_author(), value)

    def vote_answer(self, answer, value):
        answer.set_vote_count(answer.get_vote_count() + value)
        self.update_user_reputation(answer.get_author(), value)

    def update_user_reputation(self, user, value):
        user.set_reputation(user.get_reputation() + value)

    def search_questions(self, query):
        results = []
        for question in self.questions.values():
            if query in question.get_title() or query in question.get_body():
                results.append(question)
        return results

    def get_questions_by_tag(self, tag_name):
        return self.tagged_questions.get(tag_name, [])

    def get_questions_by_user(self, user):
        results = []
        for question in self.questions.values():
            if question.get_author() == user:
                results.append(question)
        return results