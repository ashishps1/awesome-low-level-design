class Post:
    def __init__(self, id, user_id, content, image_urls, video_urls, timestamp, likes, comments):
        self.id = id
        self.user_id = user_id
        self.content = content
        self.image_urls = image_urls
        self.video_urls = video_urls
        self.timestamp = timestamp
        self.likes = likes
        self.comments = comments

    def get_id(self):
        return self.id

    def get_user_id(self):
        return self.user_id

    def get_content(self):
        return self.content

    def get_image_urls(self):
        return self.image_urls

    def get_video_urls(self):
        return self.video_urls

    def get_timestamp(self):
        return self.timestamp

    def get_likes(self):
        return self.likes

    def get_comments(self):
        return self.comments