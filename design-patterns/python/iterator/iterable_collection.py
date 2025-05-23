from abc import ABC, abstractmethod
from typing import TypeVar, Generic
from .iterator import Iterator

T = TypeVar('T')

class IterableCollection(Generic[T], ABC):
    @abstractmethod
    def create_iterator(self) -> Iterator[T]:
        pass 