from abc import ABC, abstractmethod
from enums import MatchStatus

class MatchObserver(ABC):
    @abstractmethod
    def update(self, match, last_ball):
        pass

class CommentaryDisplay(MatchObserver):
    def update(self, match, last_ball):
        if match.get_current_status() == MatchStatus.FINISHED:
            print("[COMMENTARY]: Match has finished!")
        elif match.get_current_status() == MatchStatus.IN_BREAK:
            print("[COMMENTARY]: Inning has ended!")
        else:
            print(f"[COMMENTARY]: {last_ball.get_commentary()}")

class UserNotifier(MatchObserver):
    def update(self, match, last_ball):
        if match.get_current_status() == MatchStatus.FINISHED:
            print("[NOTIFICATION]: Match has finished!")
        elif match.get_current_status() == MatchStatus.IN_BREAK:
            print("[NOTIFICATION]: Inning has ended!")
        elif last_ball and last_ball.is_wicket():
            print("[NOTIFICATION]: Wicket! A player is out.")
        elif last_ball and last_ball.is_boundary():
            print(f"[NOTIFICATION]: It's a boundary! {last_ball.get_runs_scored()} runs.")

class ScorecardDisplay(MatchObserver):
    def update(self, match, last_ball):
        if match.get_current_status() == MatchStatus.FINISHED:
            print("\n--- MATCH RESULT ---")
            print(match.get_result_message().upper())
            print("--------------------")
            
            print("Player Stats:")
            counter = 1
            for inning in match.get_innings():
                print(f"Inning {counter}")
                inning.print_player_stats()
                counter += 1
        elif match.get_current_status() == MatchStatus.IN_BREAK:
            print("\n--- END OF INNINGS ---")
            last_innings = match.get_innings()[-1]
            print(f"Final Score: {last_innings.get_batting_team().get_name()}: "
                  f"{last_innings.get_score()}/{last_innings.get_wickets()} "
                  f"(Overs: {last_innings.get_overs():.1f})")
            print("------------------------")
        else:
            print("\n--- SCORECARD UPDATE ---")
            current_innings = match.get_current_innings()
            print(f"{current_innings.get_batting_team().get_name()}: "
                  f"{current_innings.get_score()}/{current_innings.get_wickets()} "
                  f"(Overs: {current_innings.get_overs():.1f})")
            print("------------------------")