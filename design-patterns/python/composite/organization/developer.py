from .employee import Employee

class Developer(Employee):
    def __init__(self, name: str, salary: float):
        self.name = name
        self.salary = salary

    def show_details(self) -> None:
        print(f"Developer: {self.name}, Salary: ${self.salary}")

    def get_salary(self) -> float:
        return self.salary 