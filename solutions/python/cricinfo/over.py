class Over:
    def __init__(self, over_number):
        self.over_number = over_number
        self.balls = []

    def add_ball(self, ball):
        self.balls.append(ball)

    def get_over_number(self):
        return self.over_number

    def get_balls(self):
        return self.balls
