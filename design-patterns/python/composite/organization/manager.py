from typing import List
from .employee import Employee

class Manager(Employee):
    def __init__(self, name: str, salary: float):
        self.name = name
        self.salary = salary
        self.subordinates: List[Employee] = []

    def add_employee(self, employee: Employee) -> None:
        self.subordinates.append(employee)

    def remove_employee(self, employee: Employee) -> None:
        self.subordinates.remove(employee)

    def show_details(self) -> None:
        print(f"Manager: {self.name}, Salary: ${self.salary}")
        print("Subordinates:")
        for employee in self.subordinates:
            employee.show_details()

    def get_salary(self) -> float:
        total_salary = self.salary
        for employee in self.subordinates:
            total_salary += employee.get_salary()
        return total_salary 