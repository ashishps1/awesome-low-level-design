from datetime import datetime
from typing import List, Dict

class Course:
    def __init__(self, code: str, name: str, instructor: str, max_capacity: int, enrolled_students: int):
        self.code = code
        self.name = name
        self.instructor = instructor
        self.max_capacity = max_capacity
        self.enrolled_students = enrolled_students

    def set_enrolled_students(self, enrolled_students: int):
        self.enrolled_students = enrolled_students

    def get_code(self) -> str:
        return self.code

    def get_name(self) -> str:
        return self.name

    def get_instructor(self) -> str:
        return self.instructor

    def get_max_capacity(self) -> int:
        return self.max_capacity

    def get_enrolled_students(self) -> int:
        return self.enrolled_students