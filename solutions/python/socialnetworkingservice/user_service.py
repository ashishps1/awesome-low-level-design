from user import User
from repository import UserRepository
from typing import Optional

class UserService:
    def __init__(self):
        self.user_repository = UserRepository.get_instance()

    def create_user(self, name: str, email: str) -> User:
        user = User(name, email)
        self.user_repository.save(user)
        return user

    def add_friend(self, user_id1: str, user_id2: str):
        user1 = self.user_repository.find_by_id(user_id1)
        user2 = self.user_repository.find_by_id(user_id2)

        user1.add_friend(user2)
        user2.add_friend(user1)

    def get_user_by_id(self, user_id: str) -> Optional[User]:
        return self.user_repository.find_by_id(user_id)