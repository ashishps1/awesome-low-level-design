from symbol import Symbol

class Player:
    def __init__(self, name: str, symbol: Symbol):
        self.name = name
        self.symbol = symbol
    
    def get_name(self):
        return self.name
    
    def get_symbol(self):
        return self.symbol