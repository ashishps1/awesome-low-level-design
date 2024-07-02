from typing import List
from course import Course

class Student:
    def __init__(self, student_id: int, name: str, email: str, registered_courses: List[Course]):
        self.id = student_id
        self.name = name
        self.email = email
        self.registered_courses = registered_courses

    def get_id(self) -> int:
        return self.id

    def get_name(self) -> str:
        return self.name

    def get_email(self) -> str:
        return self.email

    def get_registered_courses(self) -> List[Course]:
        return self.registered_courses