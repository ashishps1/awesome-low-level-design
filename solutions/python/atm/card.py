class Card:
    def __init__(self, card_number: str, pin: str):
        self._card_number = card_number
        self._pin = pin
    
    def get_card_number(self) -> str:
        return self._card_number
    
    def get_pin(self) -> str:
        return self._pin