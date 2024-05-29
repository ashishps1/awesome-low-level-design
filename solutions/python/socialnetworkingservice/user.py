class User:
    def __init__(self, id, name, email, password, profile_picture, bio, friends, posts):
        self.id = id
        self.name = name
        self.email = email
        self.password = password
        self.profile_picture = profile_picture
        self.bio = bio
        self.friends = friends
        self.posts = posts

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_email(self):
        return self.email

    def get_password(self):
        return self.password

    def get_profile_picture(self):
        return self.profile_picture

    def get_bio(self):
        return self.bio

    def get_friends(self):
        return self.friends

    def get_posts(self):
        return self.posts