from typing import List

class Profile:
    def __init__(self):
        self.profile_picture = None
        self.headline = ""
        self.summary = ""
        self.experiences = []
        self.educations = []
        self.skills = []

    @property
    def profile_picture(self):
        return self._profile_picture

    @profile_picture.setter
    def profile_picture(self, value):
        self._profile_picture = value

    @property
    def headline(self) -> str:
        return self._headline

    @headline.setter
    def headline(self, value: str):
        self._headline = value

    @property
    def summary(self) -> str:
        return self._summary

    @summary.setter
    def summary(self, value: str):
        self._summary = value

    @property
    def experiences(self) -> List:
        return self._experiences

    @property
    def educations(self) -> List:
        return self._educations

    @property
    def skills(self) -> List:
        return self._skills
