class User:
    def __init__(self, id, username, password, email, reputation):
        self.id = id
        self.username = username
        self.password = password
        self.email = email
        self.reputation = reputation

    def set_reputation(self, reputation):
        self.reputation = reputation

    def get_id(self):
        return self.id

    def get_username(self):
        return self.username

    def get_password(self):
        return self.password

    def get_email(self):
        return self.email

    def get_reputation(self):
        return self.reputation