from match_status import MatchStatus

class Match:
    def __init__(self, id, title, venue, start_time, teams):
        self.id = id
        self.title = title
        self.venue = venue
        self.start_time = start_time
        self.teams = teams
        self.status = MatchStatus.SCHEDULED

    def get_id(self):
        return self.id

    def set_status(self, status):
        self.status = status

    def get_title(self):
        return self.title
