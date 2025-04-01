class Movie:
    def __init__(self, movie_id: str, title: str, description: str, duration_in_minutes: int):
        self._id = movie_id
        self._title = title
        self._description = description
        self._duration_in_minutes = duration_in_minutes

    @property
    def duration_in_minutes(self) -> int:
        return self._duration_in_minutes
