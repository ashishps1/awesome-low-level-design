from datetime import datetime
from typing import Optional
from member import Member
from enums import ConnectionStatus

class Connection:
    def __init__(self, from_member: Member, to_member: Member):
        self.from_member = from_member
        self.to_member = to_member
        self.status = ConnectionStatus.PENDING
        self.requested_at = datetime.now()
        self.accepted_at: Optional[datetime] = None

    def get_from_member(self) -> Member:
        return self.from_member

    def get_to_member(self) -> Member:
        return self.to_member

    def get_status(self) -> ConnectionStatus:
        return self.status

    def set_status(self, status: ConnectionStatus) -> None:
        self.status = status
        if status == ConnectionStatus.ACCEPTED:
            self.accepted_at = datetime.now()