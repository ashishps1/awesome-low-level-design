class Scorecard:
    def __init__(self, id, match):
        self.id = id
        self.match = match
        self.team_scores = {}
        self.innings = []

    def update_score(self, team_id, score):
        self.team_scores[team_id] = score

    def add_innings(self, innings):
        self.innings.append(innings)

    def get_id(self):
        return self.id

    def get_match(self):
        return self.match

    def get_team_scores(self):
        return self.team_scores

    def get_innings(self):
        return self.innings
