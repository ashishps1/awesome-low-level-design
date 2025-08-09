from enums import OrderType, OrderStatus
from stock import Stock
from execution_strategy import ExecutionStrategy
from order_states import OrderState, OpenState
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from user import User

class Order:
    def __init__(self, order_id: str, user: 'User', stock: Stock, order_type: OrderType, 
                 quantity: int, price: float, execution_strategy: ExecutionStrategy, owner: 'User'):
        self.order_id = order_id
        self.user = user
        self.stock = stock
        self.type = order_type
        self.quantity = quantity
        self.price = price  # Limit price for Limit orders
        self.execution_strategy = execution_strategy
        self.owner = owner
        self.current_state = OpenState()  # Initial state
        self.status = OrderStatus.OPEN

    def cancel(self) -> None:
        self.current_state.cancel(self)

    def get_order_id(self) -> str:
        return self.order_id

    def get_user(self) -> 'User':
        return self.user

    def get_stock(self) -> Stock:
        return self.stock

    def get_type(self) -> OrderType:
        return self.type

    def get_quantity(self) -> int:
        return self.quantity

    def get_price(self) -> float:
        return self.price

    def get_status(self) -> OrderStatus:
        return self.status

    def get_execution_strategy(self) -> ExecutionStrategy:
        return self.execution_strategy

    def set_state(self, state: OrderState) -> None:
        self.current_state = state

    def set_status(self, status: OrderStatus) -> None:
        self.status = status
        self._notify_owner()

    def _notify_owner(self) -> None:
        if self.owner:
            self.owner.order_status_update(self)