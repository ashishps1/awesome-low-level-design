from match import Match
from match_status import MatchStatus
from threading import Lock

class MatchService:
    _instance = None
    _lock = Lock()

    def __init__(self):
        self.matches = {}

    @classmethod
    def get_instance(cls):
        with cls._lock:
            if cls._instance is None:
                cls._instance = cls()
        return cls._instance

    def add_match(self, match):
        self.matches[match.get_id()] = match

    def get_match(self, match_id):
        return self.matches.get(match_id)

    def get_all_matches(self):
        return list(self.matches.values())

    def update_match_status(self, match_id, status):
        match = self.get_match(match_id)
        if match:
            match.set_status(status)
