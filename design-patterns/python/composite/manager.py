from typing import List
from .employee import Employee


class Manager(Employee):
    """Composite - Manager who manages other employees"""
    
    def __init__(self, name: str, position: str, salary: float):
        self._name = name
        self._position = position
        self._salary = salary
        self._subordinates: List[Employee] = []
    
    def add_employee(self, employee: Employee) -> None:
        """Add an employee to this manager's team"""
        self._subordinates.append(employee)
    
    def remove_employee(self, employee: Employee) -> None:
        """Remove an employee from this manager's team"""
        if employee in self._subordinates:
            self._subordinates.remove(employee)
    
    def show_details(self) -> None:
        print(f"Manager: {self._name}, Position: {self._position}, Salary: ${self._salary}")
        if self._subordinates:
            print(f"  Managing {len(self._subordinates)} employees:")
            for subordinate in self._subordinates:
                print("  ", end="")
                subordinate.show_details()
    
    def get_salary(self) -> float:
        """Get total salary including all subordinates"""
        total_salary = self._salary
        for subordinate in self._subordinates:
            total_salary += subordinate.get_salary()
        return total_salary
    
    @property
    def subordinates(self) -> List[Employee]:
        return self._subordinates.copy()