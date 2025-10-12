class MatchRepository:
    def __init__(self):
        self.matches = {}

    def save(self, match):
        self.matches[match.get_id()] = match

    def find_by_id(self, match_id):
        return self.matches.get(match_id)

class PlayerRepository:
    def __init__(self):
        self.players = {}

    def save(self, player):
        self.players[player.get_id()] = player

    def find_by_id(self, player_id):
        return self.players.get(player_id)