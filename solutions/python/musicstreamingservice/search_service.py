from typing import List
from playable import Song
from artist import Artist

class SearchService:
    def search_songs_by_title(self, songs: List[Song], query: str) -> List[Song]:
        return [s for s in songs if query.lower() in s.title.lower()]
    
    def search_artists_by_name(self, artists: List[Artist], query: str) -> List[Artist]:
        return [a for a in artists if query.lower() in a.get_name().lower()]