class Team:
    def __init__(self, team_id, name, players):
        self.id = team_id
        self.name = name
        self.players = players

    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def get_players(self):
        return self.players