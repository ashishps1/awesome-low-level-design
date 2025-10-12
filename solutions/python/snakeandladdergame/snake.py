from board_entity import BoardEntity

class Snake(BoardEntity):
    def __init__(self, start: int, end: int):
        super().__init__(start, end)
        if start <= end:
            raise ValueError("Snake head must be at a higher position than its tail.")