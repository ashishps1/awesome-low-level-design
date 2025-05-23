from .employee import Employee

class Designer(Employee):
    def __init__(self, name: str, salary: float):
        self.name = name
        self.salary = salary

    def show_details(self) -> None:
        print(f"Designer: {self.name}, Salary: ${self.salary}")

    def get_salary(self) -> float:
        return self.salary 