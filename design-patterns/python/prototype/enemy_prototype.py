from abc import ABC, abstractmethod
from typing import Any


class EnemyPrototype(ABC):
    """Prototype interface for enemy cloning"""
    
    @abstractmethod
    def clone(self) -> 'EnemyPrototype':
        pass