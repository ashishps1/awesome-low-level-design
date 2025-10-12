from enum import Enum

class GameStatus(Enum):
    IN_PROGRESS = "IN_PROGRESS"
    WINNER_X = "WINNER_X"
    WINNER_O = "WINNER_O"
    DRAW = "DRAW"