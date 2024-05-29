class Question:
    def __init__(self, id, title, body, author, answers, comments, tags, vote_count):
        self.id = id
        self.title = title
        self.body = body
        self.author = author
        self.answers = answers
        self.comments = comments
        self.tags = tags
        self.vote_count = vote_count

    def set_vote_count(self, vote_count):
        self.vote_count = vote_count

    def get_id(self):
        return self.id

    def get_title(self):
        return self.title

    def get_body(self):
        return self.body

    def get_author(self):
        return self.author

    def get_answers(self):
        return self.answers

    def get_comments(self):
        return self.comments

    def get_tags(self):
        return self.tags

    def get_vote_count(self):
        return self.vote_count