from abc import ABC, abstractmethod

class Votable(ABC):
    @abstractmethod
    def vote(self, user, value):
        pass

    @abstractmethod
    def get_vote_count(self):
        pass