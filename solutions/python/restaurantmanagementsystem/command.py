from abc import ABC, abstractmethod
from typing import TYPE_CHECKING
from staff import Chef, Waiter
from order import Order

class Command(ABC):
    @abstractmethod
    def execute(self):
        pass

class PrepareOrderCommand(Command):
    def __init__(self, order: Order, chef: Chef):
        self._order = order
        self._chef = chef
    
    def execute(self):
        self._chef.prepare_order(self._order)

class ServeOrderCommand(Command):
    def __init__(self, order: Order, waiter: Waiter):
        self._order = order
        self._waiter = waiter
    
    def execute(self):
        self._waiter.serve_order(self._order)