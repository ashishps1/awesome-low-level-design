from typing import Dict, List, Optional
from order import Order
from stock import Stock
from enums import OrderType, OrderStatus
from order_states import FilledState
import threading
from collections import defaultdict

class StockExchange:
    _instance: Optional['StockExchange'] = None
    _lock = threading.Lock()

    def __new__(cls):
        if cls._instance is None:
            with cls._lock:
                if cls._instance is None:
                    cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self):
        if hasattr(self, 'initialized'):
            return
        self.buy_orders: Dict[str, List[Order]] = defaultdict(list)
        self.sell_orders: Dict[str, List[Order]] = defaultdict(list)
        self.match_lock = threading.Lock()
        self.initialized = True

    @classmethod
    def get_instance(cls) -> 'StockExchange':
        return cls()

    def place_buy_order(self, order: Order) -> None:
        self.buy_orders[order.get_stock().get_symbol()].append(order)
        self._match_orders(order.get_stock())

    def place_sell_order(self, order: Order) -> None:
        self.sell_orders[order.get_stock().get_symbol()].append(order)
        self._match_orders(order.get_stock())

    def _match_orders(self, stock: Stock) -> None:
        with self.match_lock:  # Critical section to prevent race conditions during matching
            buys = self.buy_orders.get(stock.get_symbol(), [])
            sells = self.sell_orders.get(stock.get_symbol(), [])

            if not buys or not sells:
                return

            match_found = True
            while match_found:
                match_found = False
                best_buy = self._find_best_buy(buys)
                best_sell = self._find_best_sell(sells)

                if best_buy and best_sell:
                    buy_price = stock.get_price() if best_buy.get_type() == OrderType.MARKET else best_buy.get_price()
                    sell_price = stock.get_price() if best_sell.get_type() == OrderType.MARKET else best_sell.get_price()

                    if buy_price >= sell_price:
                        self._execute_trade(best_buy, best_sell, sell_price)  # Trade at the seller's asking price
                        match_found = True

    def _execute_trade(self, buy_order: Order, sell_order: Order, trade_price: float) -> None:
        print(f"--- Executing Trade for {buy_order.get_stock().get_symbol()} at ${trade_price:.2f} ---")

        buyer = buy_order.get_user()
        seller = sell_order.get_user()

        trade_quantity = min(buy_order.get_quantity(), sell_order.get_quantity())
        total_cost = trade_quantity * trade_price

        # Perform transaction
        buyer.get_account().debit(total_cost)
        buyer.get_account().add_stock(buy_order.get_stock().get_symbol(), trade_quantity)

        seller.get_account().credit(total_cost)
        seller.get_account().remove_stock(sell_order.get_stock().get_symbol(), trade_quantity)

        # Update orders
        self._update_order_status(buy_order, trade_quantity)
        self._update_order_status(sell_order, trade_quantity)

        # Update stock's market price to last traded price
        buy_order.get_stock().set_price(trade_price)

        print("--- Trade Complete ---")

    def _update_order_status(self, order: Order, quantity_traded: int) -> None:
        # This is a simplified update logic. A real system would handle partial fills.
        order.set_status(OrderStatus.FILLED)
        order.set_state(FilledState())
        stock_symbol = order.get_stock().get_symbol()
        
        # Remove from books
        if order in self.buy_orders[stock_symbol]:
            self.buy_orders[stock_symbol].remove(order)
        if order in self.sell_orders[stock_symbol]:
            self.sell_orders[stock_symbol].remove(order)

    def _find_best_buy(self, buys: List[Order]) -> Optional[Order]:
        open_orders = [o for o in buys if o.get_status() == OrderStatus.OPEN]
        if not open_orders:
            return None
        return max(open_orders, key=lambda o: o.get_price())  # Highest limit price is best

    def _find_best_sell(self, sells: List[Order]) -> Optional[Order]:
        open_orders = [o for o in sells if o.get_status() == OrderStatus.OPEN]
        if not open_orders:
            return None
        return min(open_orders, key=lambda o: o.get_price())  # Lowest limit price is best