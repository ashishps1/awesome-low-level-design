from datetime import datetime
from typing import List

class JobPosting:
    def __init__(self, job_id: str, title: str, description: str, requirements: List[str], location: str, post_date: datetime):
        self._id = job_id
        self._title = title
        self._description = description
        self._requirements = requirements
        self._location = location
        self._post_date = post_date

    @property
    def id(self) -> str:
        return self._id

    @property
    def title(self) -> str:
        return self._title

    @property
    def description(self) -> str:
        return self._description

    @property
    def requirements(self) -> List[str]:
        return self._requirements

    @property
    def location(self) -> str:
        return self._location

    @property
    def post_date(self) -> datetime:
        return self._post_date
