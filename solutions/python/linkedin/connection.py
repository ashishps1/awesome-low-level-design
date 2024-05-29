from datetime import datetime

class Connection:
    def __init__(self, user, connection_date: datetime):
        self._user = user
        self._connection_date = connection_date

    @property
    def user(self):
        return self._user

    @property
    def connection_date(self) -> datetime:
        return self._connection_date
