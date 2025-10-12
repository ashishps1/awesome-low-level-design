from innings import Innings
from enums import MatchStatus
from match_states import ScheduledState

class Match:
    def __init__(self, match_id, team1, team2, format_strategy):
        self.id = match_id
        self.team1 = team1
        self.team2 = team2
        self.format_strategy = format_strategy
        self.innings = [Innings(team1, team2)]
        self.current_state = ScheduledState()
        self.current_status = None
        self.observers = []
        self.winner = None
        self.result_message = ""

    def process_ball(self, ball):
        self.current_state.process_ball(self, ball)

    def start_next_innings(self):
        self.current_state.start_next_innings(self)

    def create_new_innings(self):
        if len(self.innings) >= self.format_strategy.get_total_innings():
            print("Cannot create a new innings, match has already reached its limit.")
            return
        
        next_innings = Innings(self.team2, self.team1)
        self.innings.append(next_innings)

    def add_observer(self, observer):
        self.observers.append(observer)

    def remove_observer(self, observer):
        self.observers.remove(observer)

    def notify_observers(self, ball):
        for observer in self.observers:
            observer.update(self, ball)

    def get_current_innings(self):
        return self.innings[-1]

    def get_id(self):
        return self.id

    def get_team1(self):
        return self.team1

    def get_team2(self):
        return self.team2

    def get_format_strategy(self):
        return self.format_strategy

    def get_innings(self):
        return self.innings

    def get_current_status(self):
        return self.current_status

    def get_winner(self):
        return self.winner

    def get_result_message(self):
        return self.result_message

    def set_state(self, state):
        self.current_state = state

    def set_current_status(self, status):
        self.current_status = status

    def set_winner(self, winner):
        self.winner = winner

    def set_result_message(self, message):
        self.result_message = message