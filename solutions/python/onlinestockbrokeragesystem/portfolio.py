from exceptions import InsufficientStockException

class Portfolio:
    def __init__(self, account):
        self.account = account
        self.holdings = {}

    def add_stock(self, stock, quantity):
        symbol = stock.get_symbol()
        self.holdings[symbol] = self.holdings.get(symbol, 0) + quantity

    def remove_stock(self, stock, quantity):
        symbol = stock.get_symbol()
        if symbol in self.holdings:
            current_quantity = self.holdings[symbol]
            if current_quantity > quantity:
                self.holdings[symbol] = current_quantity - quantity
            elif current_quantity == quantity:
                del self.holdings[symbol]
            else:
                raise InsufficientStockException("Insufficient stock quantity in the portfolio.")
        else:
            raise InsufficientStockException("Stock not found in the portfolio.")

    def get_holdings(self):
        return self.holdings