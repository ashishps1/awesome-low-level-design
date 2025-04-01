import random

class Dice:
    MIN_VALUE = 1
    MAX_VALUE = 6

    def roll(self):
        return random.randint(Dice.MIN_VALUE, Dice.MAX_VALUE)