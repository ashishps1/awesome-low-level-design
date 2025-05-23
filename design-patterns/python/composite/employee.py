from abc import ABC, abstractmethod


class Employee(ABC):
    """Component interface for all employees"""
    
    @abstractmethod
    def show_details(self) -> None:
        pass
    
    @abstractmethod
    def get_salary(self) -> float:
        pass