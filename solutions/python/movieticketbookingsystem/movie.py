from movie_observer import MovieSubject

class Movie(MovieSubject):
    def __init__(self, movie_id: str, title: str, duration_in_minutes: int):
        super().__init__()
        self.id = movie_id
        self.title = title
        self.duration_in_minutes = duration_in_minutes

    def get_id(self) -> str:
        return self.id

    def get_title(self) -> str:
        return self.title