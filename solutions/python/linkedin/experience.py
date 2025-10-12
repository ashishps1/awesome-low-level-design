from datetime import date
from typing import Optional

class Experience:
    def __init__(self, title: str, company: str, start_date: date, end_date: Optional[date]):
        self.title = title
        self.company = company
        self.start_date = start_date
        self.end_date = end_date

    def __str__(self) -> str:
        end_str = "Present" if self.end_date is None else str(self.end_date)
        return f"{self.title} at {self.company} ({self.start_date} to {end_str})"