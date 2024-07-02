import datetime

class Comment:
    def __init__(self, id, text, author, created_at):
        self.id = id
        self.text = text
        self.author = author
        self.created_at = created_at