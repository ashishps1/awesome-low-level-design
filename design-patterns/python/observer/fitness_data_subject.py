from abc import ABC, abstractmethod
from typing import List
from .fitness_data import FitnessData
from .fitness_data_observer import FitnessDataObserver


class FitnessDataSubject(ABC):
    """Subject interface for observer pattern"""
    
    @abstractmethod
    def register_observer(self, observer: FitnessDataObserver) -> None:
        pass
    
    @abstractmethod
    def remove_observer(self, observer: FitnessDataObserver) -> None:
        pass
    
    @abstractmethod
    def notify_observers(self) -> None:
        pass