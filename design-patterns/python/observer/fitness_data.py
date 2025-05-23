from typing import List
from .fitness_data_subject import FitnessDataSubject
from .fitness_data_observer import FitnessDataObserver


class FitnessData(FitnessDataSubject):
    """Concrete Subject - maintains state and notifies observers"""
    
    def __init__(self):
        self._observers: List[FitnessDataObserver] = []
        self._steps = 0
        self._calories_burned = 0.0
        self._distance_covered = 0.0
    
    def register_observer(self, observer: FitnessDataObserver) -> None:
        self._observers.append(observer)
    
    def remove_observer(self, observer: FitnessDataObserver) -> None:
        if observer in self._observers:
            self._observers.remove(observer)
    
    def notify_observers(self) -> None:
        for observer in self._observers:
            observer.update(self)
    
    def set_fitness_data(self, steps: int, calories_burned: float, distance_covered: float) -> None:
        self._steps = steps
        self._calories_burned = calories_burned
        self._distance_covered = distance_covered
        print(f"FitnessData updated: Steps={steps}, Calories={calories_burned}, Distance={distance_covered}")
        self.notify_observers()
    
    # Getters
    @property
    def steps(self) -> int:
        return self._steps
    
    @property
    def calories_burned(self) -> float:
        return self._calories_burned
    
    @property
    def distance_covered(self) -> float:
        return self._distance_covered