from match_service import MatchService
from scorecard_service import ScorecardService

class CricinfoSystem:
    def __init__(self):
        self.match_service = MatchService.get_instance()
        self.scorecard_service = ScorecardService.get_instance()

    def add_match(self, match):
        self.match_service.add_match(match)

    def get_match(self, match_id):
        return self.match_service.get_match(match_id)

    def get_all_matches(self):
        return self.match_service.get_all_matches()

    def update_match_status(self, match_id, status):
        self.match_service.update_match_status(match_id, status)

    def create_scorecard(self, match):
        self.scorecard_service.create_scorecard(match)

    def get_scorecard(self, scorecard_id):
        return self.scorecard_service.get_scorecard(scorecard_id)

    def update_score(self, scorecard_id, team_id, score):
        self.scorecard_service.update_score(scorecard_id, team_id, score)

    def add_innings(self, scorecard_id, innings):
        self.scorecard_service.add_innings(scorecard_id, innings)
