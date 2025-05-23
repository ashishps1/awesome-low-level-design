from .employee import Employee


class Developer(Employee):
    """Leaf - Individual developer employee"""
    
    def __init__(self, name: str, position: str, salary: float):
        self._name = name
        self._position = position
        self._salary = salary
    
    def show_details(self) -> None:
        print(f"Developer: {self._name}, Position: {self._position}, Salary: ${self._salary}")
    
    def get_salary(self) -> float:
        return self._salary