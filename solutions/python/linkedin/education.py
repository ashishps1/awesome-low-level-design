class Education:
    def __init__(self, school: str, degree: str, start_year: int, end_year: int):
        self.school = school
        self.degree = degree
        self.start_year = start_year
        self.end_year = end_year

    def __str__(self) -> str:
        return f"{self.degree}, {self.school} ({self.start_year} - {self.end_year})"
