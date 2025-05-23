from abc import ABC, abstractmethod

class CharacterFlyweight(ABC):
    @abstractmethod
    def draw(self, x: int, y: int) -> None:
        pass 