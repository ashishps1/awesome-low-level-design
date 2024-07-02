from typing import List
from experience import Experience
from education import Education
from skill import Skill

class Profile:
    def __init__(self):
        self.profile_picture: str = ""
        self.headline: str = ""
        self.summary: str = ""
        self.experiences: List[Experience] = []
        self.educations: List[Education] = []
        self.skills: List[Skill] = []

    def set_summary(self, summary: str):
        self.summary = summary

    def set_headline(self, headline: str):
        self.headline = headline

    def add_experience(self, experience: Experience):
        self.experiences.append(experience)

    def add_education(self, education: Education):
        self.educations.append(education)

    def add_skill(self, skill: Skill):
        self.skills.append(skill)