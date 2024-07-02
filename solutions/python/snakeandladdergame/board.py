from snake import Snake
from ladder import Ladder

class Board:
    BOARD_SIZE = 100

    def __init__(self):
        self.snakes = []
        self.ladders = []
        self._initialize_snakes_and_ladders()

    def _initialize_snakes_and_ladders(self):
        # Initialize snakes
        self.snakes.append(Snake(16, 6))
        self.snakes.append(Snake(48, 26))
        self.snakes.append(Snake(64, 60))
        self.snakes.append(Snake(93, 73))

        # Initialize ladders
        self.ladders.append(Ladder(1, 38))
        self.ladders.append(Ladder(4, 14))
        self.ladders.append(Ladder(9, 31))
        self.ladders.append(Ladder(21, 42))
        self.ladders.append(Ladder(28, 84))
        self.ladders.append(Ladder(51, 67))
        self.ladders.append(Ladder(80, 99))

    def get_board_size(self):
        return Board.BOARD_SIZE

    def get_new_position_after_snake_or_ladder(self, position):
        for snake in self.snakes:
            if snake.get_start() == position:
                return snake.get_end()

        for ladder in self.ladders:
            if ladder.get_start() == position:
                return ladder.get_end()

        return position