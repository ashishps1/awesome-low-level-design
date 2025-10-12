from abc import ABC, abstractmethod

class DispenseChain(ABC):
    @abstractmethod
    def set_next_chain(self, next_chain: 'DispenseChain'):
        pass
    
    @abstractmethod
    def dispense(self, amount: int):
        pass
    
    @abstractmethod
    def can_dispense(self, amount: int) -> bool:
        pass