class Ball:
    def __init__(self, ball_number, bowler, batsman, result):
        self.ball_number = ball_number
        self.bowler = bowler
        self.batsman = batsman
        self.result = result

    def get_ball_number(self):
        return self.ball_number

    def get_batsman(self):
        return self.batsman

    def get_bowler(self):
        return self.bowler

    def get_result(self):
        return self.result
