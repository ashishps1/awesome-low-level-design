class Wicket:
    class Builder:
        def __init__(self, wicket_type, player_out):
            self.wicket_type = wicket_type
            self.player_out = player_out
            self.caught_by = None
            self.runout_by = None

        def caught_by(self, player):
            self.caught_by = player
            return self

        def runout_by(self, player):
            self.runout_by = player
            return self

        def build(self):
            return Wicket(self)

    def __init__(self, builder):
        self.wicket_type = builder.wicket_type
        self.player_out = builder.player_out
        self.caught_by = builder.caught_by
        self.runout_by = builder.runout_by

    def get_wicket_type(self):
        return self.wicket_type

    def get_player_out(self):
        return self.player_out

    def get_caught_by(self):
        return self.caught_by

    def get_runout_by(self):
        return self.runout_by