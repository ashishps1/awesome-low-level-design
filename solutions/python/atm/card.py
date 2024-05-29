class Card:
    def __init__(self, card_number, pin):
        self.card_number = card_number
        self.pin = pin

    def get_card_number(self):
        return self.card_number

    def get_pin(self):
        return self.pin