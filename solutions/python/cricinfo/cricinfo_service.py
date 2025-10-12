import uuid
from repository import PlayerRepository, MatchRepository
from match import Match
from match_states import LiveState, FinishedState
from enums import MatchStatus
from player import Player

class CricInfoService:
    _instance = None

    def __init__(self):
        self.match_repository = MatchRepository()
        self.player_repository = PlayerRepository()

    @classmethod
    def get_instance(cls):
        if cls._instance is None:
            cls._instance = CricInfoService()
        return cls._instance

    def create_match(self, team1, team2, format_strategy):
        match_id = str(uuid.uuid4())
        match = Match(match_id, team1, team2, format_strategy)
        self.match_repository.save(match)
        print(f"Match {format_strategy.get_format_name()} created between {team1.get_name()} and {team2.get_name()}.")
        return match

    def start_match(self, match_id):
        match = self.match_repository.find_by_id(match_id)
        if match:
            match.set_state(LiveState())
            print(f"Match {match_id} is now LIVE.")

    def process_ball_update(self, match_id, ball):
        match = self.match_repository.find_by_id(match_id)
        if match:
            match.process_ball(ball)

    def start_next_innings(self, match_id):
        match = self.match_repository.find_by_id(match_id)
        if match:
            match.start_next_innings()

    def subscribe_to_match(self, match_id, observer):
        match = self.match_repository.find_by_id(match_id)
        if match:
            match.add_observer(observer)

    def end_match(self, match_id):
        match = self.match_repository.find_by_id(match_id)
        if match:
            match.set_state(FinishedState())
            print(f"Match {match_id} has FINISHED.")

    def add_player(self, player_id, player_name, player_role):
        player = Player(player_id, player_name, player_role)
        self.player_repository.save(player)
        return player