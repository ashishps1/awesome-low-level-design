from abc import ABC, abstractmethod

class Commentable(ABC):
    @abstractmethod
    def add_comment(self, comment):
        pass

    @abstractmethod
    def get_comments(self):
        pass