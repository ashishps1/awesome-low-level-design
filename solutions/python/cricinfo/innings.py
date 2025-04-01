class Innings:
    def __init__(self, id, batting_team_id, bowling_team_id):
        self.id = id
        self.batting_team_id = batting_team_id
        self.bowling_team_id = bowling_team_id
        self.overs = []

    def add_over(self, over):
        self.overs.append(over)

    def get_id(self):
        return self.id

    def get_overs(self):
        return self.overs

    def get_batting_team_id(self):
        return self.batting_team_id

    def get_bowling_team_id(self):
        return self.bowling_team_id
