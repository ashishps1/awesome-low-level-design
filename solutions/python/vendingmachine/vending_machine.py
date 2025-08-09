from inventory import Inventory
from coin import Coin
from item import Item
from states import VendingMachineState, IdleState

class VendingMachine:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(VendingMachine, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance

    def __init__(self):
        if not hasattr(self, '_initialized') or not self._initialized:
            self.inventory = Inventory()
            self.current_state = IdleState(self)
            self.balance = 0
            self.selected_item_code = None
            self._initialized = True

    @classmethod
    def get_instance(cls):
        return cls()

    def insert_coin(self, coin: Coin) -> None:
        self.current_state.insert_coin(coin)

    def add_item(self, code: str, name: str, price: int, quantity: int) -> Item:
        item = Item(code, name, price)
        self.inventory.add_item(code, item, quantity)
        return item

    def select_item(self, code: str) -> None:
        self.current_state.select_item(code)

    def dispense(self) -> None:
        self.current_state.dispense()

    def dispense_item(self) -> None:
        item = self.inventory.get_item(self.selected_item_code)
        if self.balance >= item.get_price():
            self.inventory.reduce_stock(self.selected_item_code)
            self.balance -= item.get_price()
            print(f"Dispensed: {item.get_name()}")
            if self.balance > 0:
                print(f"Returning change: {self.balance}")
        self.reset()
        self.set_state(IdleState(self))

    def refund_balance(self) -> None:
        print(f"Refunding: {self.balance}")
        self.balance = 0

    def reset(self) -> None:
        self.selected_item_code = None
        self.balance = 0

    def add_balance(self, value: int) -> None:
        self.balance += value

    def get_selected_item(self) -> Item:
        return self.inventory.get_item(self.selected_item_code)

    def set_selected_item_code(self, code: str) -> None:
        self.selected_item_code = code

    def set_state(self, state: VendingMachineState) -> None:
        self.current_state = state

    # Getters for states and inventory
    def get_inventory(self) -> Inventory:
        return self.inventory

    def get_balance(self) -> int:
        return self.balance