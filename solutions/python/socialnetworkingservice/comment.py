from datetime import datetime

class Comment:
    def __init__(self, id, user_id, post_id, content, timestamp):
        self.id = id
        self.user_id = user_id
        self.post_id = post_id
        self.content = content
        self.timestamp = timestamp

    def get_id(self):
        return self.id

    def get_user_id(self):
        return self.user_id

    def get_post_id(self):
        return self.post_id

    def get_content(self):
        return self.content

    def get_timestamp(self):
        return self.timestamp