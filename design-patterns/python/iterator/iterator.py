from abc import ABC, abstractmethod
from typing import TypeVar, Generic

T = TypeVar('T')

class Iterator(Generic[T], ABC):
    @abstractmethod
    def has_next(self) -> bool:
        pass

    @abstractmethod
    def next(self) -> T:
        pass 