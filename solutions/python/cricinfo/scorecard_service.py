from scorecard import Scorecard
from threading import Lock
import itertools

class ScorecardService:
    _instance = None
    _lock = Lock()

    def __init__(self):
        self.scorecards = {}
        self.scorecard_id_counter = itertools.count(1)

    @classmethod
    def get_instance(cls):
        with cls._lock:
            if cls._instance is None:
                cls._instance = cls()
        return cls._instance

    def create_scorecard(self, match):
        scorecard_id = self._generate_scorecard_id(match.get_id())
        scorecard = Scorecard(scorecard_id, match)
        self.scorecards[scorecard_id] = scorecard

    def get_scorecard(self, scorecard_id):
        return self.scorecards.get(scorecard_id)

    def update_score(self, scorecard_id, team_id, score):
        scorecard = self.get_scorecard(scorecard_id)
        if scorecard:
            scorecard.update_score(team_id, score)

    def add_innings(self, scorecard_id, innings):
        scorecard = self.get_scorecard(scorecard_id)
        if scorecard:
            scorecard.add_innings(innings)

    def _generate_scorecard_id(self, match_id):
        scorecard_id = next(self.scorecard_id_counter)
        return f"SC-{match_id}-{scorecard_id:04d}"
