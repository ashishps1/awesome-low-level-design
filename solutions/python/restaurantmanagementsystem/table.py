from table_status import TableStatus

class Table:
    def __init__(self, table_id: int, capacity: int):
        self._id = table_id
        self._capacity = capacity
        self._status = TableStatus.AVAILABLE
    
    @property
    def id(self) -> int:
        return self._id
    
    @property
    def capacity(self) -> int:
        return self._capacity
    
    @property
    def status(self) -> TableStatus:
        return self._status
    
    @status.setter
    def status(self, status: TableStatus):
        self._status = status