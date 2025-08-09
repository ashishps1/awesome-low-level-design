from abc import ABC, abstractmethod
from enums import MatchStatus

class MatchState(ABC):
    @abstractmethod
    def process_ball(self, match, ball):
        pass

    def start_next_innings(self, match):
        print("ERROR: Cannot start the next innings from the current state.")

class ScheduledState(MatchState):
    def process_ball(self, match, ball):
        print("ERROR: Cannot process a ball for a match that has not started.")

class InBreakState(MatchState):
    def process_ball(self, match, ball):
        print("ERROR: Cannot process a ball. The match is currently in a break.")

    def start_next_innings(self, match):
        print("Starting the next innings...")
        match.create_new_innings()
        match.set_state(LiveState())
        match.set_current_status(MatchStatus.LIVE)

class FinishedState(MatchState):
    def process_ball(self, match, ball):
        print("ERROR: Cannot process a ball for a finished match.")

class LiveState(MatchState):
    def process_ball(self, match, ball):
        current_innings = match.get_current_innings()
        current_innings.add_ball(ball)
        match.notify_observers(ball)
        self.check_for_match_end(match)

    def check_for_match_end(self, match):
        current_innings = match.get_current_innings()
        innings_count = len(match.get_innings())
        is_final_innings = (innings_count == match.get_format_strategy().get_total_innings())

        # Win condition: Chasing team surpasses the target
        if is_final_innings:
            target_score = match.get_innings()[0].get_score() + 1
            if current_innings.get_score() >= target_score:
                wickets_remaining = (len(current_innings.get_batting_team().get_players()) - 1) - current_innings.get_wickets()
                self.declare_winner(match, current_innings.get_batting_team(), f"won by {wickets_remaining} wickets")
                return

        # End of innings condition
        if self.is_innings_over(match):
            if is_final_innings:
                score1 = match.get_innings()[0].get_score()
                score2 = current_innings.get_score()

                if score1 > score2:
                    self.declare_winner(match, match.get_team1(), f"won by {score1 - score2} runs")
                elif score2 > score1:
                    wickets_remaining = (len(current_innings.get_batting_team().get_players()) - 1) - current_innings.get_wickets()
                    self.declare_winner(match, current_innings.get_batting_team(), f"won by {wickets_remaining} wickets")
                else:
                    self.declare_winner(match, None, "Match Tied")
            else:
                print("End of the innings!")
                match.set_state(InBreakState())
                match.set_current_status(MatchStatus.IN_BREAK)
                match.notify_observers(None)

    def declare_winner(self, match, winning_team, message):
        print("MATCH FINISHED!")
        match.set_winner(winning_team)
        result_message = f"{winning_team.get_name()} {message}" if winning_team else message
        match.set_result_message(result_message)

        match.set_state(FinishedState())
        match.set_current_status(MatchStatus.FINISHED)
        match.notify_observers(None)

    def is_innings_over(self, match):
        current_innings = match.get_current_innings()
        all_out = current_innings.get_wickets() >= len(current_innings.get_batting_team().get_players()) - 1
        overs_finished = int(current_innings.get_overs()) >= match.get_format_strategy().get_total_overs()
        return all_out or overs_finished