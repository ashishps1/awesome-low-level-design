from commentary_manager import CommentaryManager

class Ball:
    class BallBuilder:
        def __init__(self):
            self.ball_number = 0
            self.bowled_by = None
            self.faced_by = None
            self.runs_scored = 0
            self.wicket = None
            self.extra_type = None
            self.commentary = None

        def with_ball_number(self, ball_number):
            self.ball_number = ball_number
            return self

        def bowled_by(self, bowler):
            self.bowled_by = bowler
            return self

        def faced_by(self, batsman):
            self.faced_by = batsman
            return self

        def with_runs(self, runs):
            self.runs_scored = runs
            return self

        def with_wicket(self, wicket):
            self.wicket = wicket
            return self

        def with_extra_type(self, extra):
            self.extra_type = extra
            return self

        def with_commentary(self, commentary):
            self.commentary = commentary
            return self

        def build(self):
            temp_ball = Ball(self)
            
            if self.commentary is None:
                self.commentary = CommentaryManager.get_instance().generate_commentary(temp_ball)
            
            return Ball(self)

    def __init__(self, builder):
        self.ball_number = builder.ball_number
        self.bowled_by = builder.bowled_by
        self.faced_by = builder.faced_by
        self.runs_scored = builder.runs_scored
        self.wicket = builder.wicket
        self.extra_type = builder.extra_type
        self.commentary = builder.commentary

    def is_wicket(self):
        return self.wicket is not None

    def is_boundary(self):
        return self.runs_scored == 4 or self.runs_scored == 6

    def get_ball_number(self):
        return self.ball_number

    def get_bowled_by(self):
        return self.bowled_by

    def get_faced_by(self):
        return self.faced_by

    def get_runs_scored(self):
        return self.runs_scored

    def get_wicket(self):
        return self.wicket

    def get_extra_type(self):
        return self.extra_type

    def get_commentary(self):
        return self.commentary