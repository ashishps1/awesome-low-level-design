from typing import List, Optional
from experience import Experience
from education import Education

class Profile:
    def __init__(self):
        self.summary: Optional[str] = None
        self.experiences: List[Experience] = []
        self.educations: List[Education] = []

    def set_summary(self, summary: str) -> None:
        self.summary = summary

    def add_experience(self, experience: Experience) -> None:
        self.experiences.append(experience)

    def add_education(self, education: Education) -> None:
        self.educations.append(education)

    def display(self) -> None:
        print(f"  Summary: {self.summary if self.summary else 'N/A'}")

        print("  Experience:")
        if not self.experiences:
            print("    - None")
        else:
            for exp in self.experiences:
                print(f"    - {exp}")

        print("  Education:")
        if not self.educations:
            print("    - None")
        else:
            for edu in self.educations:
                print(f"    - {edu}")