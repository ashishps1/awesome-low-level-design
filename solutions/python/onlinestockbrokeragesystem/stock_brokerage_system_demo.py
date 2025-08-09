from user import User
from stock_brokerage_system import StockBrokerageSystem
import time
from order_builder import OrderBuilder

def print_account_status(user: User) -> None:
    print(f"Member: {user.get_name()}, Cash: ${user.get_account().get_balance():.2f}, Portfolio: {user.get_account().get_portfolio()}")

class StockBrokerageSystemDemo:
    def run():
        # System Setup
        system = StockBrokerageSystem.get_instance()

        # Create Stocks
        apple = system.add_stock("AAPL", 150.00)
        google = system.add_stock("GOOG", 2800.00)

        # Create Members (Users)
        alice = system.register_user("Alice", 20000.00)
        bob = system.register_user("Bob", 25000.00)

        # Bob already owns some Apple stock
        bob.get_account().add_stock("AAPL", 50)

        # Members subscribe to stock notifications (Observer Pattern)
        apple.add_observer(alice)
        google.add_observer(alice)
        apple.add_observer(bob)

        print("--- Initial State ---")
        print_account_status(alice)
        print_account_status(bob)

        print("\n--- Trading Simulation Starts ---\n")

        # SCENARIO 1: Limit Order Match
        print("--- SCENARIO 1: Alice places a limit buy, Bob places a limit sell that matches ---")

        # Alice wants to buy 10 shares of AAPL if the price is $150.50 or less
        alice_buy_order = OrderBuilder() \
            .for_user(alice) \
            .buy(10) \
            .with_stock(apple) \
            .with_limit(150.50) \
            .build()
        system.place_buy_order(alice_buy_order)

        # Bob wants to sell 20 of his shares if the price is $150.50 or more
        bob_sell_order = OrderBuilder() \
            .for_user(bob) \
            .sell(20) \
            .with_stock(apple) \
            .with_limit(150.50) \
            .build()
        system.place_sell_order(bob_sell_order)

        # The exchange will automatically match and execute this trade.
        # Let's check the status after the trade.
        time.sleep(0.1)  # Give time for notifications to print
        print("\n--- Account Status After Trade 1 ---")
        print_account_status(alice)
        print_account_status(bob)

        # SCENARIO 2: Price Update triggers notifications
        print("\n--- SCENARIO 2: Market price of GOOG changes ---")
        google.set_price(2850.00)  # Alice will get a notification

        # SCENARIO 3: Order Cancellation (State Pattern)
        print("\n--- SCENARIO 3: Alice places an order and then cancels it ---")
        alice_cancel_order = OrderBuilder() \
            .for_user(alice) \
            .buy(5) \
            .with_stock(google) \
            .with_limit(2700.00) \
            .build()  # Price is too low, so it won't execute immediately
        system.place_buy_order(alice_cancel_order)

        print(f"Order status before cancellation: {alice_cancel_order.get_status().value}")
        system.cancel_order(alice_cancel_order)
        print(f"Order status after cancellation attempt: {alice_cancel_order.get_status().value}")

        # Now try to cancel an already filled order
        print("\n--- Trying to cancel an already FILLED order (State Pattern) ---")
        print(f"Bob's sell order status: {bob_sell_order.get_status().value}")
        system.cancel_order(bob_sell_order)  # This should fail
        print(f"Bob's sell order status after cancel attempt: {bob_sell_order.get_status().value}")

if __name__ == "__main__":
    StockBrokerageSystemDemo.run()