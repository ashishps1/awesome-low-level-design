class UserManager:
    _instance = None

    def __init__(self):
        self.users = {}

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = cls()
        return cls._instance

    def register_user(self, user):
        self.users[user.get_id()] = user

    def login_user(self, username, password):
        for user in self.users.values():
            if user.get_username() == username and user.get_password() == password:
                return user
        return None