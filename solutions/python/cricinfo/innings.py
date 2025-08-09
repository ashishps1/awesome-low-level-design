from enums import ExtraType
from player_stats import PlayerStats

class Innings:
    def __init__(self, batting_team, bowling_team):
        self.batting_team = batting_team
        self.bowling_team = bowling_team
        self.score = 0
        self.wickets = 0
        self.balls = []
        self.player_stats = {}
        
        for player in batting_team.get_players():
            self.player_stats[player] = PlayerStats()
        for player in bowling_team.get_players():
            self.player_stats[player] = PlayerStats()

    def add_ball(self, ball):
        self.balls.append(ball)
        runs_scored = ball.get_runs_scored()
        self.score += runs_scored
        
        if ball.get_extra_type() in [ExtraType.WIDE, ExtraType.NO_BALL]:
            self.score += 1
        else:
            ball.get_faced_by().get_stats().update_runs(runs_scored)
            ball.get_faced_by().get_stats().increment_balls_played()
            self.player_stats[ball.get_faced_by()].update_runs(runs_scored)
            self.player_stats[ball.get_faced_by()].increment_balls_played()
        
        if ball.is_wicket():
            self.wickets += 1
            ball.get_bowled_by().get_stats().increment_wickets()
            self.player_stats[ball.get_bowled_by()].increment_wickets()

    def print_player_stats(self):
        for player, stats in self.player_stats.items():
            if stats.get_balls_played() > 0 or stats.get_wickets() > 0:
                print(f"Player: {player.get_name()} - Stats: {stats}")

    def get_overs(self):
        valid_balls = sum(1 for b in self.balls 
                         if b.get_extra_type() not in [ExtraType.WIDE, ExtraType.NO_BALL])
        
        completed_overs = valid_balls // 6
        balls_in_current_over = valid_balls % 6
        
        return completed_overs + (balls_in_current_over / 10.0)

    def get_batting_team(self):
        return self.batting_team

    def get_bowling_team(self):
        return self.bowling_team

    def get_score(self):
        return self.score

    def get_wickets(self):
        return self.wickets

    def get_balls(self):
        return self.balls