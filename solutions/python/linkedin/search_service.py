from typing import Collection, List
from member import Member

class SearchService:
    def __init__(self, members: Collection[Member]):
        self.members = members

    def search_by_name(self, name: str) -> List[Member]:
        return [member for member in self.members if name.lower() in member.get_name().lower()]