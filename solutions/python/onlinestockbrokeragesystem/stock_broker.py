from queue import Queue
from threading import Lock
from account import Account
from exceptions import InsufficientFundsException, InsufficientStockException

class StockBroker:
    _instance = None
    _lock = Lock()

    def __new__(cls):
        if not cls._instance:
            with cls._lock:
                if not cls._instance:
                    cls._instance = super().__new__(cls)
                    cls._instance.accounts = {}
                    cls._instance.stocks = {}
                    cls._instance.order_queue = Queue()
                    cls._instance.account_id_counter = 1
        return cls._instance

    def create_account(self, user, initial_balance):
        account_id = self._generate_account_id()
        account = Account(account_id, user, initial_balance)
        self.accounts[account_id] = account

    def get_account(self, account_id):
        return self.accounts.get(account_id)

    def add_stock(self, stock):
        self.stocks[stock.get_symbol()] = stock

    def get_stock(self, symbol):
        return self.stocks.get(symbol)

    def place_order(self, order):
        self.order_queue.put(order)
        self._process_orders()

    def _process_orders(self):
        while not self.order_queue.empty():
            order = self.order_queue.get()
            try:
                order.execute()
            except (InsufficientFundsException, InsufficientStockException) as e:
                # Handle exception and notify user
                print(f"Order failed: {str(e)}")

    def _generate_account_id(self):
        account_id = self.account_id_counter
        self.account_id_counter += 1
        return f"A{account_id:09d}"