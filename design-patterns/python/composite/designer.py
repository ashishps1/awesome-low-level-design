from .employee import Employee


class Designer(Employee):
    """Leaf - Individual designer employee"""
    
    def __init__(self, name: str, position: str, salary: float):
        self._name = name
        self._position = position
        self._salary = salary
    
    def show_details(self) -> None:
        print(f"Designer: {self._name}, Position: {self._position}, Salary: ${self._salary}")
    
    def get_salary(self) -> float:
        return self._salary