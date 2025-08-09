from cricinfo_service import CricInfoService
from enums import PlayerRole, WicketType
from match_format_strategy import T20FormatStrategy
from team import Team
from ball import Ball
from wicket import Wicket
from match_observer import CommentaryDisplay, ScorecardDisplay, UserNotifier

class CricinfoDemo:
    @staticmethod
    def main():
        service = CricInfoService.get_instance()

        # Setup Players and Teams
        p1 = service.add_player("P1", "Virat", PlayerRole.BATSMAN)
        p2 = service.add_player("P2", "Rohit", PlayerRole.BATSMAN)
        p3 = service.add_player("P3", "Bumrah", PlayerRole.BOWLER)
        p4 = service.add_player("P4", "Jadeja", PlayerRole.ALL_ROUNDER)

        p5 = service.add_player("P5", "Warner", PlayerRole.BATSMAN)
        p6 = service.add_player("P6", "Smith", PlayerRole.BATSMAN)
        p7 = service.add_player("P7", "Starc", PlayerRole.BOWLER)
        p8 = service.add_player("P8", "Maxwell", PlayerRole.ALL_ROUNDER)

        india = Team("T1", "India", [p1, p2, p3, p4])
        australia = Team("T2", "Australia", [p5, p6, p7, p8])

        # Create a T20 Match
        t20_match = service.create_match(india, australia, T20FormatStrategy())
        match_id = t20_match.get_id()

        # Create and subscribe observers
        scorecard = ScorecardDisplay()
        commentary = CommentaryDisplay()
        notifier = UserNotifier()

        service.subscribe_to_match(match_id, scorecard)
        service.subscribe_to_match(match_id, commentary)
        service.subscribe_to_match(match_id, notifier)

        # Start the match
        service.start_match(match_id)

        print("\n--- SIMULATING FIRST INNINGS ---")
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p7).faced_by(p1).with_runs(2).build())
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p7).faced_by(p1).with_runs(1).build())
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p7).faced_by(p2).with_runs(6).build())

        p2_wicket = Wicket.Builder(WicketType.BOWLED, p2).build()
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p7).faced_by(p2).with_runs(0).with_wicket(p2_wicket).build())

        p3_wicket = Wicket.Builder(WicketType.LBW, p3).build()
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p7).faced_by(p3).with_runs(0).with_wicket(p3_wicket).build())

        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p7).faced_by(p4).with_runs(4).build())

        p4_wicket = Wicket.Builder(WicketType.CAUGHT, p4).caught_by(p6).build()
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p7).faced_by(p4).with_runs(0).with_wicket(p4_wicket).build())

        print("\n\n--- INNINGS BREAK ---")
        print("Players are off the field. Preparing for the second innings.")

        # Start the second innings
        service.start_next_innings(match_id)

        print("\n--- SIMULATING SECOND INNINGS ---")
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p3).faced_by(p5).with_runs(4).build())

        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p3).faced_by(p5).with_runs(1).build())

        p5_wicket = Wicket.Builder(WicketType.BOWLED, p5).build()
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p3).faced_by(p5).with_runs(0).with_wicket(p5_wicket).build())

        p7_wicket = Wicket.Builder(WicketType.LBW, p7).build()
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p3).faced_by(p7).with_runs(0).with_wicket(p7_wicket).build())

        p8_wicket = Wicket.Builder(WicketType.STUMPED, p8).build()
        service.process_ball_update(match_id, Ball.BallBuilder()
                                   .bowled_by(p3).faced_by(p8).with_runs(0).with_wicket(p8_wicket).build())

        service.end_match(match_id)

if __name__ == "__main__":
    CricinfoDemo.main()