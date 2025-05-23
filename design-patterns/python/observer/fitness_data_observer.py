from abc import ABC, abstractmethod


class FitnessDataObserver(ABC):
    """Observer interface"""
    
    @abstractmethod
    def update(self, fitness_data) -> None:
        pass