from abc import ABC, abstractmethod
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .vending_machine import VendingMachine


class MachineState(ABC):
    """State interface for vending machine states"""
    
    @abstractmethod
    def insert_coin(self, machine: 'VendingMachine') -> None:
        pass
    
    @abstractmethod
    def select_item(self, machine: 'VendingMachine') -> None:
        pass
    
    @abstractmethod
    def dispense_item(self, machine: 'VendingMachine') -> None:
        pass
    
    @abstractmethod
    def cancel_transaction(self, machine: 'VendingMachine') -> None:
        pass