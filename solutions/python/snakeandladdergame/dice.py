import random

class Dice:
    def __init__(self, min_value: int, max_value: int):
        self.min_value = min_value
        self.max_value = max_value

    def roll(self) -> int:
        return random.randint(self.min_value,self.max_value)
