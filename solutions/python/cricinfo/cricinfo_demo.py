from datetime import datetime
from player import Player
from team import Team
from match import Match
from cricinfo_system import CricinfoSystem
from innings import Innings
from over import Over
from ball import Ball

class CricinfoDemo:
    @staticmethod
    def run():
        # Create teams
        team1_players = [
            Player("P101", "Player 1", "Batsman"),
            Player("P102", "Player 2", "Bowler"),
            Player("P103", "Player 3", "All-rounder")
        ]
        team2_players = [
            Player("P201", "Player 4", "Batsman"),
            Player("P202", "Player 5", "Bowler"),
            Player("P203", "Player 6", "All-rounder")
        ]
        team1 = Team("T1", "Team 1", team1_players)
        team2 = Team("T2", "Team 2", team2_players)
        teams = [team1, team2]

        # Create a match
        match = Match("M001", "Match 1", "Venue 1", datetime.now(), teams)

        # Create Cricinfo system
        cricinfo_system = CricinfoSystem()

        # Add the match to the system
        cricinfo_system.add_match(match)

        # Create a scorecard for the match
        cricinfo_system.create_scorecard(match)

        # Get the scorecard
        scorecard_id = "SC-M001-0001"
        scorecard = cricinfo_system.get_scorecard(scorecard_id)

        # Update scores
        cricinfo_system.update_score(scorecard_id, "T1", 100)
        cricinfo_system.update_score(scorecard_id, "T2", 75)

        # Create innings
        innings1 = Innings("I1", "T1", "T2")
        innings2 = Innings("I2", "T2", "T1")

        # Add overs to innings
        over1 = Over(1)
        over1.add_ball(Ball(1, "P202", "P101", "4"))
        over1.add_ball(Ball(2, "P202", "P101", "6"))
        innings1.add_over(over1)

        over2 = Over(2)
        over2.add_ball(Ball(1, "P102", "P201", "1"))
        over2.add_ball(Ball(2, "P102", "P201", "0"))
        innings1.add_over(over2)

        # Add innings to the scorecard
        cricinfo_system.add_innings(scorecard_id, innings1)
        cricinfo_system.add_innings(scorecard_id, innings2)

        # Get the updated scorecard
        updated_scorecard = cricinfo_system.get_scorecard(scorecard_id)

        # Display the scorecard
        print("Scorecard ID:", updated_scorecard.get_id())
        print("Match:", updated_scorecard.get_match().get_title())
        print("Team Scores:")
        for team_id, score in updated_scorecard.get_team_scores().items():
            print(f"{team_id}: {score}")
        print("Innings:")
        for innings in updated_scorecard.get_innings():
            print("Innings ID:", innings.get_id())
            print("Batting Team:", innings.get_batting_team_id())
            print("Bowling Team:", innings.get_bowling_team_id())
            print("Overs:")
            for over in innings.get_overs():
                print("Over", over.get_over_number())
                for ball in over.get_balls():
                    print(f"Ball {ball.get_ball_number()}: {ball.get_bowler()} to {ball.get_batsman()} - {ball.get_result()}")
                print()

if __name__ == "__main__":
    CricinfoDemo.run()