from stock_broker import StockBroker
from user import User
from stock import Stock
from buy_order import BuyOrder
from sell_order import SellOrder

class StockBrokerageSystemDemo:
    def run():
        stock_broker = StockBroker()

        # Create user and account
        user = User("U001", "John Doe", "john@example.com")
        stock_broker.create_account(user, 10000.0)
        account = stock_broker.get_account("A000000001")

        # Add stocks to the stock broker
        stock1 = Stock("AAPL", "Apple Inc.", 150.0)
        stock2 = Stock("GOOGL", "Alphabet Inc.", 2000.0)
        stock_broker.add_stock(stock1)
        stock_broker.add_stock(stock2)

        # Place buy orders
        buy_order1 = BuyOrder("O001", account, stock1, 10, 150.0)
        buy_order2 = BuyOrder("O002", account, stock2, 5, 2000.0)
        stock_broker.place_order(buy_order1)
        stock_broker.place_order(buy_order2)

        # Place sell orders
        sell_order1 = SellOrder("O003", account, stock1, 5, 160.0)
        stock_broker.place_order(sell_order1)

        # Print account balance and portfolio
        print(f"Account Balance: ${account.get_balance()}")
        print(f"Portfolio: {account.get_portfolio().get_holdings()}")

if __name__ == "__main__":
    StockBrokerageSystemDemo.run()