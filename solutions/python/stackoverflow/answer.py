class Answer:
    def __init__(self, id, body, author, question, comments, vote_count):
        self.id = id
        self.body = body
        self.author = author
        self.question = question
        self.comments = comments
        self.vote_count = vote_count

    def set_vote_count(self, vote_count):
        self.vote_count = vote_count

    def get_id(self):
        return self.id

    def get_body(self):
        return self.body

    def get_author(self):
        return self.author

    def get_question(self):
        return self.question

    def get_comments(self):
        return self.comments

    def get_vote_count(self):
        return self.vote_count