class Stock:
    def __init__(self, symbol, name, price):
        self.symbol = symbol
        self.name = name
        self.price = price

    def update_price(self, new_price):
        self.price = new_price

    def get_symbol(self):
        return self.symbol

    def get_name(self):
        return self.name

    def get_price(self):
        return self.price