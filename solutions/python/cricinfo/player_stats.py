class PlayerStats:
    def __init__(self):
        self.runs = 0
        self.balls_played = 0
        self.wickets = 0

    def update_runs(self, run_scored):
        self.runs += run_scored

    def increment_balls_played(self):
        self.balls_played += 1

    def increment_wickets(self):
        self.wickets += 1

    def get_runs(self):
        return self.runs

    def get_balls_played(self):
        return self.balls_played

    def get_wickets(self):
        return self.wickets

    def __str__(self):
        return f"Runs: {self.runs}, Balls Played: {self.balls_played}, Wickets: {self.wickets}"