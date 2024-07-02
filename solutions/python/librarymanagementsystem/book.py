class Book:
    def __init__(self, isbn: str, title: str, author: str, publication_year: int):
        self._isbn = isbn
        self._title = title
        self._author = author
        self._publication_year = publication_year
        self._available = True

    @property
    def isbn(self) -> str:
        return self._isbn

    @property
    def title(self) -> str:
        return self._title

    @property
    def author(self) -> str:
        return self._author

    @property
    def publication_year(self) -> int:
        return self._publication_year

    @property
    def available(self) -> bool:
        return self._available

    @available.setter
    def available(self, available: bool):
        self._available = available
