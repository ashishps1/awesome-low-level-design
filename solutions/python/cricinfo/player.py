from player_stats import PlayerStats

class Player:
    def __init__(self, player_id, name, role):
        self.id = player_id
        self.name = name
        self.role = role
        self.stats = PlayerStats()

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_role(self):
        return self.role

    def get_stats(self):
        return self.stats